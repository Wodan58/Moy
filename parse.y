%{
/*
    module  : parse.y
    version : 1.2
    date    : 12/27/15
*/
#include <stdio.h>
#include <gc.h>
#define YYMALLOC  GC_malloc
#define YYFREE(X) ((X)?X=0:0)
#define PARSER

int yyerror(), yylex();
%}

%token <str> JSymbol String
%token <num> Boolean Char Int
%token <dbl> Float
%token <set> Set
%token <lis> List

%token MODULE
%token <ent> JPRIVATE
%token JPUBLIC
%token EQUAL
%token END

%type <num> char_or_int
%type <set> opt_set set
%type <lis> opt_quot quot opt_term term list factor
%type <ent> opt_module module opt_private private

%{
#ifdef BIT_32
#define long_t	long
#else
#define long_t	long long
#endif
%}

%union YYSTYPE {
    int flag;
    char dummy;
    clock_t cur;
    unsigned char ch;

    long_t num;
    long_t set;
    char *str;
    double dbl;
    FILE *fil;
    struct Node *lis;
    struct Entry *ent;
    void (*proc) ();
};

%{
#include "globals1.h"
%}

%%

/*
    Cycle is the top-level target of the grammar.
*/
script : cycle { writeln(); } ;

cycle : cycle def_or_term END { writestack(); } | /* empty */ ;

def_or_term : compound_def | opt_term { exeterm($1); } ;

/*
    A compound definition is an optional module, followed by an optional
    private section, followed by a public section.
*/
compound_def : opt_module opt_private public { exitpriv($2); exitmod($1); }
	     | /* empty */ ;

opt_module : module | /* empty */ { $$ = 0; } ;

module : MODULE JSymbol { $$ = initmod($2); } ;

opt_private : private | /* empty */ { $$ = (Entry *)-1; } ;

private : JPRIVATE { $1 = initpriv(); } seq_definition { stoppriv(); } ;

opt_public : public | /* empty */ ;

public : JPUBLIC seq_definition ;

/*
    A definition sequence is one or more definitions, separated by ';' .
*/
seq_definition : seq_definition ';' opt_definition | opt_definition ;

/*
    A definition is an atomic symbol and a term, separated by '==' .
*/
opt_definition : JSymbol EQUAL opt_quot
		 { enteratom($1, $3); }
	       | private public END { exitpriv($1); }
	       | module opt_private opt_public END
		 { exitpriv($2); exitmod($1); }
	       | /* empty */ ;

/*
    A term is one or more factors.
*/
opt_term : term { $$ = reverse($1); } ;

term : term factor { $2->next = $1; $$ = $2; } | factor ;

/*
    A quotation is similar to a term.
*/
opt_quot : quot { $$ = reverse($1); } | /* empty */ { $$ = 0; } ;

quot : quot factor { $2->next = $1; $$ = $2; } | factor ;

/*
    A factor is a constant, or a list, or a set.
*/
factor  : JSymbol { $$ = newnode(JSymbol, (Types) $1, 0); }
	| Boolean { $$ = newnode(BOOLEAN_, (Types) $1, 0); }
	| Char { $$ = newnode(CHAR_, (Types) $1, 0); }
	| Int { $$ = newnode(INTEGER_, (Types) $1, 0); }
	| Float { $$ = newnode(FLOAT_, (Types) $1, 0); }
	| String { $$ = newnode(STRING_, (Types) $1, 0); }
	| list { $$ = newnode(LIST_, (Types) $1, 0); }
	| set { $$ = newnode(SET_, (Types) $1, 0); }
	;

list : '[' opt_quot ']' { $$ = $2; } ;

set : '{' opt_set '}' { $$ = $2; } ;

opt_set : opt_set char_or_int { $$ |= 1 << $2; } | /* empty */ { $$ = 0; } ;

char_or_int : Char | Int ;
