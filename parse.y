%{
/*
    module  : parse.y
    version : 1.26
    date    : 06/16/22
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

%type <num> char_or_int
%type <set> opt_set set
%type <lis> opt_term term factor list

%union {
    long num;		/* USR, BOOLEAN, CHAR, INTEGER */
    proc_t proc;	/* ANON_FUNCT */
    long set;		/* SET */
    char *str;		/* SYMBOL, STRING */
    struct Node *lis;	/* LIST */
    double dbl;		/* FLOAT */
    FILE *fil;		/* FILE */
    void *ptr;		/* GENERIC */
};

%%

/*
    Cycle is the top-level target of the grammar.
*/
cycle : cycle def_or_term END | /* empty */ { initialise(env); } ;

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

private : JPRIVATE { initpriv(env,1); } seq_definition { stoppriv(); } ;

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

opt_term : term { $$ = reverse($1); } | /* empty */ { $$ = 0; } ;

/*
    A term is one or more factors.
*/
term : term factor { $2->next = $1; $$ = $2; } | factor ;

/*
    A factor is a constant, or a list, or a set.
*/
factor  : USR_	      { env->bucket.num = lookup(env, $1);
			$$ = newnode(USR_, env->bucket, 0); }
	| BOOLEAN_    { env->bucket.num = $1;
			$$ = newnode(BOOLEAN_, env->bucket, 0); }
	| CHAR_       { env->bucket.num = $1;
			$$ = newnode(CHAR_, env->bucket, 0); }
	| INTEGER_    { env->bucket.num = $1;
			$$ = newnode(INTEGER_, env->bucket, 0); }
	| STRING_     { env->bucket.str = $1;
			$$ = newnode(STRING_, env->bucket, 0); }
	| FLOAT_      { env->bucket.dbl = $1;
			$$ = newnode(FLOAT_, env->bucket, 0); }
	| list        { env->bucket.lis = $1;
			$$ = newnode(LIST_, env->bucket, 0); }
	| set         { env->bucket.set = $1;
			$$ = newnode(SET_, env->bucket, 0); } ;

list : '[' opt_term ']' { $$ = $2; } ;

set : '{' opt_set '}' { $$ = $2; } ;

opt_set : opt_set char_or_int { if ($2 < 0 || $2 >= SETSIZE_)
				yyerror(env, "small numeric expected in set");
				else $$ |= (long)1 << $2; }
	| /* empty */ { $$ = 0; } ;

char_or_int : CHAR_ | INTEGER_ ;
