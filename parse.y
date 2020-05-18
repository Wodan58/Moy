%{
/*
    module  : parse.y
    version : 1.25
    date    : 03/28/20
*/
#include <stdio.h>
#include <stdlib.h>
#define PARSER
#include "joy.h"
%}

%token MODULE JPRIVATE JPUBLIC JEQUAL END

%token <num> USR_		2
%token <proc> ANON_FUNCT_	3
%token <num> BOOLEAN_		4
%token <num> CHAR_		5
%token <num> INTEGER_		6
%token <set> SET_		7
%token <str> STRING_		8
%token <lis> LIST_		9
%token <dbl> FLOAT_		10
%token <fil> FILE_		11
%token <str> SYMBOL_		12

%type <num> char_or_int
%type <set> opt_set set
%type <lis> opt_term term factor list

%union {
    long_t num;
    ulong_t set;
    char *str;
    real_t dbl;
    FILE *fil;
    struct Node *lis;
    void (*proc)(void);
    void *ptr;
};

%{
#include "symbol.h"
%}

%%

/*
    Cycle is the top-level target of the grammar.
*/
cycle : cycle def_or_term END | /* empty */ ;

def_or_term : compound_def | opt_term { execute($1); } ;

/*
    A compound definition is an optional module, followed by an optional
    private section, followed by a public section.
*/
compound_def : opt_module opt_private public { exitpriv(); exitmod(); } ;

opt_module : module | /* empty */ ;

module : MODULE SYMBOL_ { initmod($2); } ;

opt_private : private | /* empty */ ;

private : JPRIVATE { initpriv(); } seq_definition { stoppriv(); } ;

opt_public : public | /* empty */ ;

public : JPUBLIC { initpub(); } seq_definition { exitpub(); } ;

/*
    A definition sequence is one or more definitions, separated by ';' .
*/
seq_definition : seq_definition ';' opt_definition | opt_definition ;

/*
    A definition is an atomic symbol and a term, separated by '==' .
*/
opt_definition : SYMBOL_ JEQUAL opt_term { enteratom($1, $3); }
	       | private public END { exitpriv(); }
	       | module opt_private opt_public END { exitpriv(); exitmod(); }
	       | /* empty */ ;

opt_term : term { $$ = reverse($1); } | /* empty */ { $$ = 0; } ;

/*
    A term is one or more factors.
*/
term : term factor { $2->next = $1; $$ = $2; } | factor ;

/*
    A factor is a constant, or a list, or a set.
*/
factor  : SYMBOL_ { $$ = newnode(USR_, (void *)(long_t)lookup($1), 0); }
	| BOOLEAN_ { $$ = newnode(BOOLEAN_, (void *)$1, 0); }
	| CHAR_ { $$ = newnode(CHAR_, (void *)$1, 0); }
	| INTEGER_ { $$ = newnode(INTEGER_, (void *)$1, 0); }
	| STRING_ { $$ = newnode(STRING_, $1, 0); }
	| FLOAT_ { $$ = dblnode($1, 0); }
	| list { $$ = newnode(LIST_, $1, 0); }
	| set { $$ = newnode(SET_, (void *)$1, 0); }
	;

list : '[' opt_term ']' { $$ = $2; } ;

set : '{' opt_set '}' { $$ = $2; } ;

opt_set : opt_set char_or_int { $$ |= (long_t)1 << $2; }
	| /* empty */ { $$ = 0; } ;

char_or_int : CHAR_ | INTEGER_ ;
