%{
/*
    module  : pars.y
    version : 1.2
    date    : 07/12/23
*/
#include "globals.h"
%}

%lex-param	{env}
%parse-param	{pEnv env}

%token MODULE JPRIVATE JPUBLIC JEQUAL END

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
%token <str> USR_PRIME_		12
%token <proc> ANON_PRIME_	13

%type <num> char_or_int
%type <set> opt_set set
%type <lis> opt_term term factor list

%union {
    long num;		/* USR, BOOLEAN, CHAR, INTEGER */
    proc_t proc;	/* ANON_FUNCT */
    unsigned long set;	/* SET */
    char *str;		/* STRING */
    NodeList *lis;	/* LIST */
    double dbl;		/* FLOAT */
    FILE *fil;		/* FILE */
    pEntry ent;		/* SYMBOL */
};

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

private : JPRIVATE { initpriv(env, 1); } seq_definition { stoppriv(); } ;

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
definition : USR_ JEQUAL opt_term { enteratom(env, $1, $3); }
	   | private opt_public END { exitpriv(); }
	   | module opt_private opt_public END { exitmod(); } ;

opt_term : term | /* empty */ { $$ = 0; } ;

/*
    A term is one or more factors.
*/
term : term factor { int i, j; for (i = 0, j = vec_size($1); i < j; i++)
		     vec_push($2, vec_at($1, i)); $$ = $2; }
     | factor ;

/*
    A factor is a constant, or a list, or a set.
*/
factor  : USR_      {   NodeList *list = 0; Node node; Entry ent;
			lookup(env, $1);
			if (!env->location && strchr($1, '.'))
			    yyerror(env, "no such field in module");
			else {
			    ent = sym_at(env->symtab, env->location);
			    /* execute immediate functions at compile time */
			    if (ent.flags == IMMEDIATE) {
				(*ent.u.proc)(env);
				node = vec_pop(env->stck);
			    } else if (ent.is_user) {
				node.u.ent = env->location;
				node.op = USR_;
			    } else {
				node.u.proc = ent.u.proc;
				node.op = ANON_FUNCT_;
			    }
                            vec_init(list);
			    vec_push(list, node);
			}
			$$ = list;
		    }
	| CHAR_     { YYSTYPE u; u.num = $1; $$ = newnode(CHAR_, u); }
	| INTEGER_  { YYSTYPE u; u.num = $1; $$ = newnode(INTEGER_, u); }
	| STRING_   { YYSTYPE u; u.str = $1; $$ = newnode(STRING_, u); }
	| FLOAT_    { YYSTYPE u; u.dbl = $1; $$ = newnode(FLOAT_, u); }
	| list      { YYSTYPE u; u.lis = $1; $$ = newnode(LIST_, u); }
	| set       { YYSTYPE u; u.set = $1; $$ = newnode(SET_, u); } ;

list : '[' opt_term ']' { $$ = $2; } ;

set : '{' opt_set '}' { $$ = $2; } ;

opt_set : opt_set char_or_int { if ($2 < 0 || $2 >= SETSIZE)
				yyerror(env, "small numeric expected in set");
				else $$ |= (long)1 << $2; }
	| /* empty */ { $$ = 0; } ;

char_or_int : CHAR_ | INTEGER_ ;
