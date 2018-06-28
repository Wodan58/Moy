%{
/*
    module  : parse.y
    version : 1.19
    date    : 06/28/18
*/
#include <stdio.h>
#include <stdlib.h>
#define PARSER
#include "joy.h"
%}

%token <num> Symbol	250
%token <str> SYMBOL_	1
%token <str> USR_	2
%token <proc> ANON_FUNCT_	3
%token <num> BOOLEAN_	4
%token <num> CHAR_	5
%token <num> INTEGER_	6
%token <set> SET_	7
%token <str> STRING_	8
%token <lis> LIST_	9
%token <dbl> FLOAT_	10
%token <fil> FILE_	11

%token DO_NOTHING	12
%token DO_FALSE		13
%token DO_TRUE		14
%token DO_MAXINT	15
%token DO_SETSIZE	16
%token DO_STACK		17
%token DO_SYMTABMAX	18
%token DO_SYMTABINDEX	19
%token DO_DUMP		20
%token DO_CONTS		21
%token DO_AUTOPUT	22
%token DO_UNDEFERROR	23
%token DO_UNDEFS	24
%token DO_ECHO		25
%token DO_CLOCK		26
%token DO_TIME		27
%token DO_RAND		28
%token DO_MEMORYMAX	29
%token DO_STDIN		30
%token DO_STDOUT	31
%token DO_STDERR	32
%token DO_ID		33
%token DO_DUP		34
%token DO_OVER		35
%token DO_PICK		36
%token DO_SWAP		37
%token DO_ROLLUP	38
%token DO_ROLLDOWN	39
%token DO_ROTATE	40
%token DO_POPD		41
%token DO_MUL		42
%token DO_PLUS		43
%token DO_DUPD		44
%token DO_MINUS		45
%token DO_STOP		46
%token DO_DIVIDE	47
%token DO_SWAPD		48
%token DO_ROLLUPD	49
%token DO_ROLLDOWND	50
%token DO_ROTATED	51
%token DO_POP		52
%token DO_CHOICE	53
%token DO_OR		54
%token DO_XOR		55
%token DO_AND		56
%token DO_NOT		57
%token DO_REM		58
%token DO_LESS		60
%token DO_EQL		61
%token DO_GREATER	62
%token DO_DIV		63
%token DO_SIGN		64
%token DO_NEG		65
%token DO_ORD		66
%token DO_CHR		67
%token DO_ABS		68
%token DO_ACOS		69
%token DO_ASIN		70
%token DO_ATAN		71
%token DO_ATAN2		72
%token DO_CEIL		73
%token DO_COS		74
%token DO_COSH		75
%token DO_EXP		76
%token DO_FLOOR		77
%token DO_ROUND		78
%token DO_FREXP		79
%token DO_LDEXP		80
%token DO_LOG		81
%token DO_LOG10		82
%token DO_MODF		83
%token DO_POW		84
%token DO_SIN		85
%token DO_SINH		86
%token DO_SQRT		87
%token DO_TAN		88
%token DO_TANH		89
%token DO_TRUNC		90
%token DO_LOCALTIME	92
%token DO_GMTIME	94
%token DO_MKTIME	95
%token DO_STRFTIME	96
%token DO_STRTOL	97
%token DO_STRTOD	98
%token DO_FORMAT	99
%token DO_FORMATF	100
%token DO_SRAND		101
%token DO_PRED		102
%token DO_SUCC		103
%token DO_MAX		104
%token DO_MIN		105
%token DO_FCLOSE	106
%token DO_FEOF		107
%token DO_FERROR	108
%token DO_FFLUSH	109
%token DO_FGET		110
%token DO_FGETCH	111
%token DO_FGETS 	112
%token DO_FOPEN		113
%token DO_FREAD		114
%token DO_FWRITE	115
%token DO_FREMOVE	116
%token DO_FRENAME	117
%token DO_FILETIME	118
%token DO_FPUT		119
%token DO_FPUTCH	120
%token DO_FPUTCHARS	121
%token DO_FPUTSTRING	122
%token DO_FSEEK		124
%token DO_FTELL		126
%token DO_UNSTACK	127
%token DO_CONS		128
%token DO_SWONS		129
%token DO_FIRST		130
%token DO_REST		131
%token DO_COMPARE	132
%token DO_INDEX		133
%token DO_AT		134
%token DO_OF		135
%token DO_SIZE		136
%token DO_CASTING	137
%token DO_OPCASE	138
%token DO_CASE		139
%token DO_UNCONS	140
%token DO_UNSWONS	141
%token DO_DROP		142
%token DO_TAKE		143
%token DO_CONCAT	144
%token DO_ENCONCAT	145
%token DO_NAME		146
%token DO_INTERN	147
%token DO_BODY		148
%token DO_NULL		149
%token DO_SMALL		150
%token DO_GEQL		151
%token DO_LEQL		152
%token DO_NEQL		153
%token DO_EQUAL		154
%token DO_HAS		155
%token DO_IN		156
%token DO_SAMETYPE	157
%token DO_INTEGER	158
%token DO_CHAR		159
%token DO_LOGICAL	160
%token DO_SET		161
%token DO_STRING	162
%token DO_LIST		163
%token DO_LEAF		164
%token DO_USER		165
%token DO_FLOAT		166
%token DO_FILE		167
%token DO_I		168
%token DO_X		169
%token DO_DIP		170
%token DO_APP1		171
%token DO_APP11		172
%token DO_APP12		173
%token DO_CONSTRUCT	174
%token DO_NULLARY	175
%token DO_UNARY		176
%token DO_UNARY2	177
%token DO_UNARY3	178
%token DO_UNARY4	179
%token DO_APP2		180
%token DO_APP3		181
%token DO_APP4		182
%token DO_BINARY	183
%token DO_TERNARY	184
%token DO_CLEAVE	185
%token DO_BRANCH	186
%token DO_IFTE		187
%token DO_IFINTEGER	188
%token DO_IFCHAR	189
%token DO_IFLOGICAL	190
%token DO_IFSET		191
%token DO_IFSTRING	192
%token DO_IFLIST	193
%token DO_IFFLOAT	194
%token DO_IFFILE	195
%token DO_COND		196
%token DO_WHILE		197
%token DO_LINREC	198
%token DO_TAILREC	199
%token DO_BINREC	200
%token DO_GENREC	201
%token DO_CONDNESTREC	202
%token DO_CONDLINREC	203
%token DO_STEP		204
%token DO_FOLD		205
%token DO_MAP		206
%token DO_TIMES		207
%token DO_INFRA		208
%token DO_PRIMREC	209
%token DO_FILTER	210
%token DO_SPLIT		211
%token DO_SOME		212
%token DO_ALL		213
%token DO_TREESTEP	214
%token DO_TREEREC	215
%token DO_TREEGENREC	216
%token DO_HELP		217
%token DO_HELP1		218
%token DO_HELPDETAIL	219
%token DO_MANUAL	220
%token DO_HTML_MANUAL	221
%token DO_LATEX_MANUAL	222
%token DO_MANUAL_LIST	223
%token DO_SETTRACEGC	224
%token DO_SETAUTOPUT	225
%token DO_SETUNDEFERROR	226
%token DO_SETECHO	227
%token DO_GC		228
%token DO_SYSTEM	229
%token DO_GETENV	230
%token DO_ARGV		231
%token DO_ARGC		232
%token DO_MEMORYINDEX	233
%token DO_GET		234
%token DO_GETCH		235
%token DO_PUT		236
%token DO_PUTCH		237
%token DO_PUTCHARS	238
%token DO_INCLUDE	239
%token DO_ABORT		240
%token DO_QUIT		241

%token MODULE		251
%token <ent> JPRIVATE	252
%token JPUBLIC		253
%token JEQUAL		254
%token END		255

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

module : MODULE USR_ { initmod($2); } ;

opt_private : private | /* empty */ ;

private : JPRIVATE { initpriv(); } seq_definition { stoppriv(); } ;

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
factor  : Symbol { $$ = newnode($1, (void *)$1, 0); }
	| USR_ { $$ = newnode(USR_, (void *)lookup($1), 0); }
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
