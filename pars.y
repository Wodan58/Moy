%{
/*
    module  : pars.y
    version : 1.19
    date    : 09/17/24
*/
#include "globals.h"

static uint64_t list2set(pEnv env, NodeList list)
{
    int i;
    Node node;
    uint64_t set = 0;

    for (i = vec_size(list) - 1; i >= 0; i--) {
	node = vec_at(list, i);
	if (node.op == CHAR_ || node.op == INTEGER_)
	    if (node.u.num < 0 || node.u.num >= SETSIZE)
		yyerror(env, "small numeric expected in set");
	    else
		set |= (uint64_t)1 << node.u.num;
	else
	    yyerror(env, "numeric expected in set");
    }
    return set;
}
%}

%lex-param	{env}
%parse-param	{pEnv env}

%token MODULE_ PRIVATE PUBLIC EQDEF END CONST_

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

%type <set> set
%type <lis> opt_term term factor list

/* generate include file with symbols and types */
%defines

/* advanced semantic type */
%union {
    int64_t num;	/* USR, BOOLEAN, CHAR, INTEGER */
    proc_t proc;	/* ANON_FUNCT */
    uint64_t set;	/* SET */
    char *str;		/* STRING */
    NodeList lis;	/* LIST */
    double dbl;		/* FLOAT */
    FILE *fil;		/* FILE */
    int ent;		/* SYMBOL */
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

module : MODULE_ USR_ { initmod(env, $2); } ;

opt_private : private | /* empty */ ;

private : PRIVATE { initpriv(env); } seq_definition { stoppriv(); } ;

opt_public : public | /* empty */ ;

public : PUBLIC seq_definition | CONST_ { env->inlining = 1; }
         seq_definition { env->inlining = 0; } ;

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

opt_term : term | /* empty */ { vec_init($$); } ;

/*
    A term is one or more factors.
*/
term : term factor { vec_concat($$, $2, $1); }
     | factor ;

/*
    A factor is a constant, or a list, or a set.
*/
factor  : USR_      {   int index; Entry ent; Node node;
			index = lookup(env, $1);
			if (!index && strchr($1, '.'))
			    my_error("no such field in module", &@1);
			ent = vec_at(env->symtab, index);
			/* evaluate immediate functions at compile time */
			if (ent.flags == IMMEDIATE) {
			    if (ent.is_user)
				evaluate(env, ent.u.body);
			    else
				(*ent.u.proc)(env);
			    node = vec_pop(env->stck);
			 } else if (ent.is_user) {
			    node.u.ent = index;
			    node.op = USR_;
			 } else {
			    node.u.proc = ent.u.proc;
			    node.op = ANON_FUNCT_;
			 }
			 vec_init($$);
			 vec_push($$, node);
		    }
	| CHAR_     { YYSTYPE u; u.num = $1; $$ = newnode(CHAR_, u); }
	| INTEGER_  { YYSTYPE u; u.num = $1; $$ = newnode(INTEGER_, u); }
	| STRING_   { YYSTYPE u; u.str = $1; $$ = newnode(STRING_, u); }
	| BIGNUM_   {
		      #ifdef USE_BIGNUM_ARITHMETIC
		      YYSTYPE u; u.str = $1; $$ = newnode(BIGNUM_, u);
		      #endif
		    }
	| FLOAT_    { YYSTYPE u; u.dbl = $1; $$ = newnode(FLOAT_, u); }
	| list      { YYSTYPE u; u.lis = $1; $$ = newnode(LIST_, u); }
	| set       { YYSTYPE u; u.set = $1; $$ = newnode(SET_, u); } ;

list : '[' opt_term ']' { $$ = $2; } ;

set : '{' opt_term '}' { $$ = list2set(env, $2); } ;
