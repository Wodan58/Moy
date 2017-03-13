%{
/*
    module  : parse.y
    version : 1.13
    date    : 03/12/17
*/
#include <stdio.h>
#include <stdlib.h>
#define PARSER
#include "joy.h"
%}

%token <num> Symbol BOOLEAN_ CHAR_ INTEGER_
%token <set> SET_
%token <str> STRING_
%token <lis> LIST_
%token <dbl> FLOAT_
%token <fil> FILE_
%token <ent> USR_
%token <proc> ANON_FUNCT_
%token <str> SYMBOL_

%token MODULE
%token <ent> JPRIVATE
%token JPUBLIC
%token JEQUAL
%token END

%token DO_NOTHING DO_FALSE DO_TRUE DO_MAXINT DO_SETSIZE DO_STACK DO_SYMTABMAX
%token DO_SYMTABINDEX DO_DUMP DO_CONTS DO_AUTOPUT DO_UNDEFERROR DO_UNDEFS
%token DO_ECHO DO_CLOCK DO_TIME DO_RAND DO_MEMORYMAX DO_STDIN DO_STDOUT
%token DO_STDERR DO_ID DO_DUP DO_SWAP DO_ROLLUP DO_ROLLDOWN DO_ROTATE DO_POPD
%token DO_DUPD DO_SWAPD DO_ROLLUPD DO_ROLLDOWND DO_ROTATED DO_POP DO_CHOICE
%token DO_OR DO_XOR DO_AND DO_NOT DO_PLUS DO_MINUS DO_MUL DO_DIVIDE DO_REM
%token DO_DIV DO_SIGN DO_NEG DO_ORD DO_CHR DO_ABS DO_ACOS DO_ASIN DO_ATAN
%token DO_ATAN2 DO_CEIL DO_COS DO_COSH DO_EXP DO_FLOOR DO_ROUND DO_FREXP
%token DO_LDEXP DO_LOG DO_LOG10 DO_MODF DO_POW DO_SIN DO_SINH DO_SQRT DO_TAN
%token DO_TANH DO_TRUNC DO_LOCALTIME DO_GMTIME DO_MKTIME DO_STRFTIME DO_STRTOL
%token DO_STRTOD DO_FORMAT DO_FORMATF DO_SRAND DO_PRED DO_SUCC DO_MAX DO_MIN
%token DO_FCLOSE DO_FEOF DO_FERROR DO_FFLUSH DO_FGET DO_FGETCH DO_FGETS 
%token DO_FOPEN DO_FREAD DO_FWRITE DO_FREMOVE DO_FRENAME DO_FILETIME DO_FPUT
%token DO_FPUTCH DO_FPUTCHARS DO_FPUTSTRING DO_FSEEK DO_FTELL DO_UNSTACK
%token DO_CONS DO_SWONS DO_FIRST DO_REST DO_COMPARE DO_AT DO_OF DO_SIZE
%token DO_OPCASE DO_CASE DO_UNCONS DO_UNSWONS DO_DROP DO_TAKE DO_CONCAT
%token DO_ENCONCAT DO_NAME DO_INTERN DO_BODY DO_NULL DO_SMALL DO_GEQL
%token DO_GREATER DO_LEQL DO_LESS DO_NEQL DO_EQL DO_EQUAL DO_HAS DO_IN DO_INDEX
%token DO_SAMETYPE DO_CASTING DO_INTEGER DO_CHAR DO_LOGICAL DO_SET DO_STRING
%token DO_LIST DO_LEAF DO_USER DO_FLOAT DO_FILE DO_I DO_X DO_DIP DO_APP1
%token DO_APP11 DO_APP12 DO_CONSTRUCT DO_NULLARY DO_UNARY DO_UNARY2 DO_UNARY3
%token DO_UNARY4 DO_APP2 DO_APP3 DO_APP4 DO_BINARY DO_TERNARY DO_CLEAVE
%token DO_BRANCH DO_IFTE DO_IFINTEGER DO_IFCHAR DO_IFLOGICAL DO_IFSET
%token DO_IFSTRING DO_IFLIST DO_IFFLOAT DO_IFFILE DO_COND DO_WHILE DO_LINREC
%token DO_TAILREC DO_BINREC DO_GENREC DO_CONDNESTREC DO_CONDLINREC DO_STEP
%token DO_FOLD DO_MAP DO_TIMES DO_INFRA DO_PRIMREC DO_FILTER DO_SPLIT DO_SOME
%token DO_ALL DO_TREESTEP DO_TREEREC DO_TREEGENREC DO_HELP DO_HELP1
%token DO_HELPDETAIL DO_MANUAL DO_HTML_MANUAL DO_LATEX_MANUAL DO_MANUAL_LIST
%token DO_SETTRACEGC DO_SETAUTOPUT DO_SETUNDEFERROR DO_SETECHO DO_GC DO_SYSTEM
%token DO_GETENV DO_ARGV DO_ARGC DO_MEMORYINDEX DO_GET DO_GETCH DO_PUT DO_PUTCH
%token DO_PUTCHARS DO_INCLUDE DO_ABORT DO_QUIT

%type <num> char_or_int
%type <set> opt_set set
%type <lis> opt_term term factor list
%type <ent> opt_module module opt_private private

%union YYSTYPE {
    long_t num;
    ulong_t set;
    char *str;
    real_t dbl;
    FILE *fil;
    struct Node *lis;
    struct Entry *ent;
    void (*proc)(void);
    char ch;
    int bool;
    void *ptr;
    unsigned flag;
};

%{
#include "symbol.h"
%}

%%

/*
    Cycle is the top-level target of the grammar.
*/
cycle : cycle def_or_term END | /* empty */ { stk = memory; } ;

def_or_term : compound_def | term { execute(reverse($1)); } ;

/*
    A compound definition is an optional module, followed by an optional
    private section, followed by a public section.
*/
compound_def : opt_module opt_private public { exitpriv($2); exitmod($1); }
	     | /* empty */ { execute(0); } ;

opt_module : module | /* empty */ { $$ = 0; } ;

module : MODULE USR_ { $$ = initmod($2); } ;

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
opt_definition : USR_ JEQUAL opt_term
		 { enteratom($1, $3); }
	       | private public END { exitpriv($1); }
	       | module opt_private opt_public END
		 { exitpriv($2); exitmod($1); }
	       | /* empty */ ;

opt_term : term { $$ = reverse($1); } | /* empty */ { $$ = 0; } ;

/*
    A term is one or more factors.
*/
term : term factor { $2->next = $1; $$ = $2; } | factor ;

/*
    A factor is a constant, or a list, or a set.
*/
factor  : Symbol { $$ = newnode($1, (void *)$1, 0); }
	| USR_ { $$ = newnode(USR_, $1, 0); }
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

opt_set : opt_set char_or_int { $$ |= 1 << $2; } | /* empty */ { $$ = 0; } ;

char_or_int : CHAR_ | INTEGER_ ;
