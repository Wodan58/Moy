%{
/*
    module  : pars.y
    version : 1.11
    date    : 10/02/23
*/
#include "globals.h"
%}

%lex-param	{env}
%parse-param	{pEnv env}

%token MODULE JPRIVATE JPUBLIC EQDEF END

%token <num> KEYWORD_		1
%token <str> USR_		2
%token <proc> ANON_FUNCT_	3
%token <num> BOOLEAN_		4
%token <num> CHAR_		5
%token <num> INTEGER_		6
%token <set> SET_		7
%token <str> STRING_		8
%token <lis> LIST_		9
%token <dbl> FLOAT_		10
%token <fil> FILE_		11
%token <str> BIGNUM_		12
%token <str> USR_PRIME_		13
%token <proc> ANON_PRIME_	14
%token <str> USR_STRING_	15
%token <lis> USR_LIST_		16

%type <num> char_or_int
%type <set> opt_set set
%type <lis> opt_term term factor list

/* generate include file with symbols and types */
%defines

/* advanced semantic type */
%union {
    int64_t num;	/* USR, BOOLEAN, CHAR, INTEGER */
    proc_t proc;	/* ANON_FUNCT */
    uint64_t set;	/* SET */
    char *str;		/* STRING */
    NodeList *lis;	/* LIST */
    double dbl;		/* FLOAT */
    FILE *fil;		/* FILE */
    pEntry ent;		/* SYMBOL */
};

/* start the grammar with cycle */
%start cycle

%%

/*
    Cycle is the top-level target of the grammar.
*/
cycle : cycle def_or_term END | /* empty */ ;

def_or_term : compound_def | opt_term { execute(env, $1); } ;

/*
    A compound definition is an optional module, followed by an optional
    private section, followed by a public section.
*/
compound_def : public
	     | private opt_public { exitpriv(); }
	     | module opt_private opt_public { exitmod(); } ;

module : MODULE USR_ { initmod(env, $2); } ;

opt_private : private | /* empty */ ;

private : JPRIVATE { initpriv(env); } seq_definition { stoppriv(); } ;

opt_public : public | /* empty */ ;

public : JPUBLIC seq_definition ;

/*
    A definition sequence is one or more definitions, separated by ';' .
*/
seq_definition : seq_definition ';' opt_definition | opt_definition ;

/*
    An optional definition is a definition or nothing at all.
*/
opt_definition : definition | /* empty */ ;

/*
    A definition is an atomic symbol and a term, separated by '==' .
*/
definition : USR_ EQDEF opt_term { enteratom(env, $1, $3); }
	   | private opt_public END { exitpriv(); }
	   | module opt_private opt_public END { exitmod(); } ;

opt_term : term | /* empty */ { $$ = 0; } ;

/*
    A term is one or more factors.
*/
term : term factor { int i, j; for (i = 0, j = pvec_cnt($1); i < j; i++)
		     $2 = pvec_add($2, pvec_nth($1, i)); $$ = $2; }
     | factor ;

/*
    A factor is a constant, or a list, or a set.
*/
factor  : USR_      {   Entry ent; Node node;
			lookup(env, $1);
			if (!env->location && strchr($1, '.'))
			    my_error("no such field in module", &@1);
			else {
			    ent = vec_at(env->symtab, env->location);
			    /* execute immediate functions at compile time */
			    if (ent.flags == IMMEDIATE) {
				(*ent.u.proc)(env);
				env->stck = pvec_pop(env->stck, &node);
			    } else if (ent.is_user) {
				node.u.ent = env->location;
				node.op = USR_;
			    } else {
				if (env->compiling)
				    node.u.str = ent.name;
				else
				    node.u.proc = ent.u.proc;
				node.op = ANON_FUNCT_;
			    }
			    $$ = pvec_add(pvec_init(), node);
			}
		    }
	| CHAR_     { YYSTYPE u; u.num = $1; $$ = newnode(CHAR_, u); }
	| INTEGER_  { YYSTYPE u; u.num = $1; $$ = newnode(INTEGER_, u); }
	| STRING_   { YYSTYPE u; u.str = $1; $$ = newnode(STRING_, u); }
	| BIGNUM_   { YYSTYPE u; u.str = $1; $$ = newnode(BIGNUM_, u); }
	| FLOAT_    { YYSTYPE u; u.dbl = $1; $$ = newnode(FLOAT_, u); }
	| list      { YYSTYPE u; u.lis = $1; $$ = newnode(LIST_, u); }
	| set       { YYSTYPE u; u.set = $1; $$ = newnode(SET_, u); } ;

list : '[' opt_term ']' { $$ = $2; } ;

set : '{' opt_set '}' { $$ = $2; } ;

opt_set : opt_set char_or_int { if ($2 < 0 || $2 >= SETSIZE) my_error(
				    "small numeric expected in set", &@2);
				else $$ |= (int64_t)1 << $2; }
	| /* empty */ { $$ = 0; } ;

char_or_int : CHAR_ | INTEGER_ ;
