%{
/*
    module  : parse.y
    version : 1.16
    date    : 10/23/17
*/
#include <stdio.h>
#include <stdlib.h>
#define PARSER
#include "joy.h"
%}

%token DO_NOTHING	1
%token DO_FALSE		2
%token DO_TRUE		3
%token DO_MAXINT	4
%token DO_SETSIZE	5
%token DO_STACK		6
%token DO_SYMTABMAX	7
%token DO_SYMTABINDEX	8
%token DO_DUMP		9
%token DO_CONTS		10
%token DO_AUTOPUT	11
%token DO_UNDEFERROR	12
%token DO_UNDEFS	13
%token DO_ECHO		14
%token DO_CLOCK		15
%token DO_TIME		16
%token DO_RAND		17
%token DO_MEMORYMAX	18
%token DO_STDIN		19
%token DO_STDOUT	20
%token DO_STDERR	21
%token DO_ID		22
%token DO_DUP		23
%token DO_OVER		24
%token DO_PICK		25
%token DO_SWAP		26
%token DO_ROLLUP	27
%token DO_ROLLDOWN	28
%token DO_ROTATE	29
%token DO_POPD		30
%token DO_DUPD		31
%token DO_SWAPD		32
%token DO_ROLLUPD	33
%token DO_ROLLDOWND	34
%token DO_ROTATED	35
%token DO_POP		36
%token DO_CHOICE	37
%token DO_OR		38
%token DO_XOR		39
%token DO_AND		40
%token DO_NOT		41
%token DO_MUL		42
%token DO_PLUS		43
%token DO_REM		44
%token DO_MINUS		45
%token DO_STOP		46
%token DO_DIVIDE	47
%token DO_DIV		48
%token DO_SIGN		49
%token DO_NEG		50
%token DO_ORD		51
%token DO_CHR		52
%token DO_ABS		53
%token DO_ACOS		54
%token DO_ASIN		55
%token DO_ATAN		56
%token DO_ATAN2		57
%token DO_CEIL		58
%token SEMI		59
%token DO_LESS		60
%token DO_EQL		61
%token DO_GREATER	62
%token DO_COS		63
%token DO_COSH		64
%token DO_EXP		65
%token DO_FLOOR		66
%token DO_ROUND		67
%token DO_FREXP		68
%token DO_LDEXP		69
%token DO_LOG		70
%token DO_LOG10		71
%token DO_MODF		72
%token DO_POW		73
%token DO_SIN		74
%token DO_SINH		75
%token DO_SQRT		76
%token DO_TAN		77
%token DO_TANH		78
%token DO_TRUNC		79
%token DO_LOCALTIME	80
%token DO_GMTIME	81
%token DO_MKTIME	82
%token DO_STRFTIME	83
%token DO_STRTOL	84
%token DO_STRTOD	85
%token DO_FORMAT	86
%token DO_FORMATF	87
%token DO_SRAND		88
%token DO_PRED		89
%token DO_SUCC		90
%token LBRACK		91
%token DO_MAX		92
%token RBRACK		93
%token DO_MIN		94
%token DO_FCLOSE	95
%token DO_FEOF		96
%token DO_FERROR	97
%token DO_FFLUSH	98
%token DO_FGET		99
%token DO_FGETCH	100
%token DO_FGETS 	101
%token DO_FOPEN		102
%token DO_FREAD		103
%token DO_FWRITE	104
%token DO_FREMOVE	105
%token DO_FRENAME	106
%token DO_FILETIME	107
%token DO_FPUT		108
%token DO_FPUTCH	109
%token DO_FPUTCHARS	110
%token DO_FPUTSTRING	111
%token DO_FSEEK		112
%token DO_FTELL		113
%token DO_UNSTACK	114
%token DO_CONS		115
%token DO_SWONS		116
%token DO_FIRST		117
%token DO_REST		118
%token DO_COMPARE	119
%token DO_AT		120
%token DO_OF		121
%token DO_SIZE		122
%token LBRACE		123
%token DO_OPCASE	124
%token RBRACE		125
%token DO_CASE		126
%token DO_UNCONS	127
%token DO_UNSWONS	128
%token DO_DROP		129
%token DO_TAKE		130
%token DO_CONCAT	131
%token DO_ENCONCAT	132
%token DO_NAME		133
%token DO_INTERN	134
%token DO_BODY		135
%token DO_NULL		136
%token DO_SMALL		137
%token DO_GEQL		138
%token DO_LEQL		139
%token DO_NEQL		140
%token DO_EQUAL		141
%token DO_HAS		142
%token DO_IN		143
%token DO_INDEX		144
%token DO_SAMETYPE	145
%token DO_CASTING	146
%token DO_INTEGER	147
%token DO_CHAR		148
%token DO_LOGICAL	149
%token DO_SET		150
%token DO_STRING	151
%token DO_LIST		152
%token DO_LEAF		153
%token DO_USER		154
%token DO_FLOAT		155
%token DO_FILE		156
%token DO_I		157
%token DO_X		158
%token DO_DIP		159
%token DO_APP1		160
%token DO_APP11		161
%token DO_APP12		162
%token DO_CONSTRUCT	163
%token DO_NULLARY	164
%token DO_UNARY		165
%token DO_UNARY2	166
%token DO_UNARY3	167
%token DO_UNARY4	168
%token DO_APP2		169
%token DO_APP3		170
%token DO_APP4		171
%token DO_BINARY	172
%token DO_TERNARY	173
%token DO_CLEAVE	174
%token DO_BRANCH	175
%token DO_IFTE		176
%token DO_IFINTEGER	177
%token DO_IFCHAR	178
%token DO_IFLOGICAL	179
%token DO_IFSET		180
%token DO_IFSTRING	181
%token DO_IFLIST	182
%token DO_IFFLOAT	183
%token DO_IFFILE	184
%token DO_COND		185
%token DO_WHILE		186
%token DO_LINREC	187
%token DO_TAILREC	188
%token DO_BINREC	189
%token DO_GENREC	190
%token DO_CONDNESTREC	191
%token DO_CONDLINREC	192
%token DO_STEP		193
%token DO_FOLD		194
%token DO_MAP		195
%token DO_TIMES		196
%token DO_INFRA		197
%token DO_PRIMREC	198
%token DO_FILTER	199
%token DO_SPLIT		200
%token DO_SOME		201
%token DO_ALL		202
%token DO_TREESTEP	203
%token DO_TREEREC	204
%token DO_TREEGENREC	205
%token DO_HELP		206
%token DO_HELP1		207
%token DO_HELPDETAIL	208
%token DO_MANUAL	209
%token DO_HTML_MANUAL	210
%token DO_LATEX_MANUAL	211
%token DO_MANUAL_LIST	212
%token DO_SETTRACEGC	213
%token DO_SETAUTOPUT	214
%token DO_SETUNDEFERROR	215
%token DO_SETECHO	216
%token DO_GC		217
%token DO_SYSTEM	218
%token DO_GETENV	219
%token DO_ARGV		220
%token DO_ARGC		221
%token DO_MEMORYINDEX	222
%token DO_GET		223
%token DO_GETCH		224
%token DO_PUT		225
%token DO_PUTCH		226
%token DO_PUTCHARS	227
%token DO_INCLUDE	228
%token DO_ABORT		229
%token DO_QUIT		230
%token MODULE		231
%token <ent> JPRIVATE	232
%token JPUBLIC		233
%token JEQUAL		234
%token END		235
%token <num> Symbol	236
%token <num> BOOLEAN_	237
%token <num> CHAR_	238
%token <num> INTEGER_	239
%token <set> SET_	240
%token <str> STRING_	241
%token <lis> LIST_	242
%token <dbl> FLOAT_	243
%token <fil> FILE_	244
%token <ent> USR_	245
%token <proc> ANON_FUNCT_	246
%token <str> SYMBOL_	247

%type <num> char_or_int
%type <set> opt_set set
%type <lis> opt_term term factor list
%type <ent> opt_module module opt_private private

%union {
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
seq_definition : seq_definition SEMI opt_definition | opt_definition ;

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

list : LBRACK opt_term RBRACK { $$ = $2; } ;

set : LBRACE opt_set RBRACE { $$ = $2; } ;

opt_set : opt_set char_or_int { $$ |= 1 << $2; } | /* empty */ { $$ = 0; } ;

char_or_int : CHAR_ | INTEGER_ ;
