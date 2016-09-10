%{
/*
    module  : parse.y
    version : 1.4
    date    : 09/10/16
*/
#include <stdio.h>
#include <time.h>
#include "memory.h"

#define PARSER

int yyerror(char *str), yylex(void), yyparse(void);
%}

%token <str> SYMBOL_ USR_ STRING_
%token <num> Symbol BOOLEAN_ CHAR_ INTEGER_
%token <dbl> FLOAT_
%token <set> SET_
%token <lis> LIST_
%token <fil> FILE_
%token <proc> ANON_FUNCT_

%token MODULE
%token <ent> JPRIVATE
%token JPUBLIC
%token JEQUAL
%token END

%token FALSE TRUE MAXINT SETSIZE STACK __SYMTABMAX __SYMTABINDEX __DUMP CONTS
%token AUTOPUT UNDEFERROR UNDEFS ECHO_ CLOCK TIME RAND __MEMORYMAX STDIN STDOUT
%token STDERR ID DUP SWAP ROLLUP ROLLDOWN ROTATE POPD DUPD SWAPD ROLLUPD
%token ROLLDOWND ROTATED POP CHOICE OR XOR AND NOT PLUS MINUS MUL DIVIDE REM
%token DIV SIGN NEG ORD CHR ABS ACOS ASIN ATAN ATAN2 CEIL COS COSH EXP FLOOR
%token ROUND FREXP LDEXP LOG LOG10 MODF POW SIN SINH SQRT TAN TANH TRUNC
%token LOCALTIME GMTIME MKTIME STRFTIME STRTOL STRTOD FORMAT FORMATF SRAND PRED
%token SUCC MAX MIN FCLOSE FEOF FERROR FFLUSH FGET FGETCH FGETS FOPEN FREAD
%token FWRITE FREMOVE FRENAME FILETIME FPUT FPUTCH FPUTCHARS APP0 FSEEK FTELL
%token UNSTACK CONS SWONS FIRST REST COMPARE AT OF SIZE OPCASE CASE UNCONS
%token UNSWONS DROP TAKE CONCAT ENCONCAT NAME INTERN BODY NULL_ SMALL GEQL
%token GREATER LEQL LESS NEQL EQL EQUAL HAS IN SAMETYPE CASTING INTEGER CHAR
%token LOGICAL SET STRING LIST LEAF USER FLOAT _FILE_ I X DIP APP1 APP11 APP12
%token CONSTRUCT NULLARY UNARY UNARY2 UNARY3 UNARY4 APP2 APP3 APP4 BINARY
%token TERNARY CLEAVE BRANCH IFTE IFINTEGER IFCHAR IFLOGICAL IFSET IFSTRING
%token IFLIST IFFLOAT IFFILE COND WHILE LINREC TAILREC BINREC GENREC
%token CONDNESTREC CONDLINREC STEP FOLD MAP TIMES INFRA PRIMREC FILTER SPLIT
%token SOME ALL TREESTEP TREEREC TREEGENREC HELP _HELP HELPDETAIL MANUAL
%token __HTML_MANUAL __LATEX_MANUAL __MANUAL_LIST __SETTRACEGC SETAUTOPUT
%token SETUNDEFERROR SETECHO GC SYSTEM GETENV ARGV ARGC __MEMORYINDEX GET GETCH
%token PUT PUTCH PUTCHARS INCLUDE ABORT QUIT

%type <num> char_or_int
%type <set> opt_set set
%type <lis> opt_quot quot opt_term term list factor
%type <ent> opt_module module opt_private private

%{
#ifdef BIT_32
#define long_t	long
#define real_t	float
#endif

#ifdef BIT_64
#define long_t	long long
#define real_t	double
#endif
%}

%union YYSTYPE {
    long_t num;
    long_t set;
    void *ptr;
    char *str;
    real_t dbl;
    FILE *fil;
    struct Node *lis;
    struct Entry *ent;
    void (*proc)(void);
};

%{
#include "globals1.h"
#include "compile.h"
%}

%%

/*
    Cycle is the top-level target of the grammar.
*/
script : cycle ;

cycle : cycle def_or_term END | /* empty */ ;

def_or_term : compound_def
	    | opt_term { if (compiling) compile($1); else execute($1); } ;

/*
    A compound definition is an optional module, followed by an optional
    private section, followed by a public section.
*/
compound_def : opt_module opt_private public { exitpriv($2); exitmod($1); }
	     | /* empty */ { if (compiling) compile(0); else writestack(); }

opt_module : module | /* empty */ { $$ = 0; } ;

module : MODULE SYMBOL_ { $$ = initmod($2); } ;

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
opt_definition : SYMBOL_ JEQUAL opt_quot
		 { enteratom($1, $3); }
	       | private public END { exitpriv($1); }
	       | module opt_private opt_public END
		 { exitpriv($2); exitmod($1); }
	       | /* empty */ ;

/*
    A term is one or more factors.
*/
opt_term : term { if (!compiling) $$ = reverse($1); } ;

term : term factor { $2->next = $1; $$ = $2; } | factor ;

/*
    A quotation is similar to a term.
*/
opt_quot : quot { if (!compiling) $$ = reverse($1); }
	 | /* empty */ { $$ = 0; } ;

quot : quot factor { $2->next = $1; $$ = $2; } | factor ;

/*
    A factor is a constant, or a list, or a set.
*/
factor  : Symbol { $$ = newnode(Symbol, (void *)$1, 0); }
	| SYMBOL_ { $$ = newnode(SYMBOL_, (void *)$1, 0); }
	| BOOLEAN_ { $$ = newnode(BOOLEAN_, (void *)$1, 0); }
	| CHAR_ { $$ = newnode(CHAR_, (void *)$1, 0); }
	| INTEGER_ { $$ = newnode(INTEGER_, (void *)$1, 0); }
	| FLOAT_ { $$ = dblnode($1, 0); /* FLOAT_ */ }
	| STRING_ { $$ = newnode(STRING_, $1, 0); }
	| list { $$ = newnode(LIST_, $1, 0); }
	| set { $$ = newnode(SET_, (void *)$1, 0); }
	;

list : '[' opt_quot ']' { $$ = $2; } ;

set : '{' opt_set '}' { $$ = $2; } ;

opt_set : opt_set char_or_int { $$ |= 1 << $2; } | /* empty */ { $$ = 0; } ;

char_or_int : CHAR_ | INTEGER_ ;
