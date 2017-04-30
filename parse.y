%{
/*
    module  : parse.y
    version : 1.14
    date    : 04/30/17
*/
#include <stdio.h>
#include <stdlib.h>
#define PARSER
#include "joy.h"
%}

%token DO_NOTHING	1
%token DO_FALSE	2
%token DO_TRUE	3
%token DO_MAXINT	4
%token DO_SETSIZE	5
%token DO_STACK	6
%token DO_SYMTABMAX	7
%token DO_SYMTABINDEX	8
%token DO_DUMP	9
%token DO_CONTS	10
%token DO_AUTOPUT	11
%token DO_UNDEFERROR	12
%token DO_UNDEFS	13
%token DO_ECHO	14
%token DO_CLOCK	15
%token DO_TIME	16
%token DO_RAND	17
%token DO_MEMORYMAX	18
%token DO_STDIN	19
%token DO_STDOUT	20
%token DO_STDERR	21
%token DO_ID	22
%token DO_DUP	23
%token DO_SWAP	24
%token DO_ROLLUP	25
%token DO_ROLLDOWN	26
%token DO_ROTATE	27
%token DO_POPD	28
%token DO_DUPD	29
%token DO_SWAPD	30
%token DO_ROLLUPD	31
%token DO_ROLLDOWND	32
%token DO_ROTATED	33
%token DO_POP	34
%token DO_CHOICE	35
%token DO_OR	36
%token DO_XOR	37
%token DO_AND	38
%token DO_NOT	39
%token DO_REM	40
%token DO_DIV	41
%token DO_MUL	42
%token DO_PLUS	43
%token DO_SIGN	44
%token DO_MINUS	45
%token DO_STOP	46
%token DO_DIVIDE	47
%token DO_NEG	48
%token DO_ORD	49
%token DO_CHR	50
%token DO_ABS	51
%token DO_ACOS	52
%token DO_ASIN	53
%token DO_ATAN	54
%token DO_ATAN2	55
%token DO_CEIL	56
%token DO_COS	57
%token DO_COSH	58
%token SEMI	59
%token DO_LESS	60
%token DO_EQL	61
%token DO_GREATER	62
%token DO_EXP	63
%token DO_FLOOR	64
%token DO_ROUND	65
%token DO_FREXP	66
%token DO_LDEXP	67
%token DO_LOG	68
%token DO_LOG10	69
%token DO_MODF	70
%token DO_POW	71
%token DO_SIN	72
%token DO_SINH	73
%token DO_SQRT	74
%token DO_TAN	75
%token DO_TANH	76
%token DO_TRUNC	77
%token DO_LOCALTIME	78
%token DO_GMTIME	79
%token DO_MKTIME	80
%token DO_STRFTIME	81
%token DO_STRTOL	82
%token DO_STRTOD	83
%token DO_FORMAT	84
%token DO_FORMATF	85
%token DO_SRAND	86
%token DO_PRED	87
%token DO_SUCC	88
%token DO_MAX	89
%token DO_MIN	90
%token LBRACK	91
%token DO_FCLOSE	92
%token RBRACK	93
%token DO_FEOF	94
%token DO_FERROR	95
%token DO_FFLUSH	96
%token DO_FGET	97
%token DO_FGETCH	98
%token DO_FGETS 	99
%token DO_FOPEN	100
%token DO_FREAD	101
%token DO_FWRITE	102
%token DO_FREMOVE	103
%token DO_FRENAME	104
%token DO_FILETIME	105
%token DO_FPUT	106
%token DO_FPUTCH	107
%token DO_FPUTCHARS	108
%token DO_FPUTSTRING	109
%token DO_FSEEK	110
%token DO_FTELL	111
%token DO_UNSTACK	112
%token DO_CONS	113
%token DO_SWONS	114
%token DO_FIRST	115
%token DO_REST	116
%token DO_COMPARE	117
%token DO_AT	118
%token DO_OF	119
%token DO_SIZE	120
%token DO_OPCASE	121
%token DO_CASE	122
%token LBRACE	123
%token DO_UNCONS	124
%token RBRACE	125
%token DO_UNSWONS	126
%token DO_DROP	127
%token DO_TAKE	128
%token DO_CONCAT	129
%token DO_ENCONCAT	130
%token DO_NAME	131
%token DO_INTERN	132
%token DO_BODY	133
%token DO_NULL	134
%token DO_SMALL	135
%token DO_GEQL	136
%token DO_LEQL	137
%token DO_NEQL	138
%token DO_EQUAL	139
%token DO_HAS	140
%token DO_IN	141
%token DO_INDEX	142
%token DO_SAMETYPE	143
%token DO_CASTING	144
%token DO_INTEGER	145
%token DO_CHAR	146
%token DO_LOGICAL	147
%token DO_SET	148
%token DO_STRING	149
%token DO_LIST	150
%token DO_LEAF	151
%token DO_USER	152
%token DO_FLOAT	153
%token DO_FILE	154
%token DO_I	155
%token DO_X	156
%token DO_DIP	157
%token DO_APP1	158
%token DO_APP11	159
%token DO_APP12	160
%token DO_CONSTRUCT	161
%token DO_NULLARY	162
%token DO_UNARY	163
%token DO_UNARY2	164
%token DO_UNARY3	165
%token DO_UNARY4	166
%token DO_APP2	167
%token DO_APP3	168
%token DO_APP4	169
%token DO_BINARY	170
%token DO_TERNARY	171
%token DO_CLEAVE	172
%token DO_BRANCH	173
%token DO_IFTE	174
%token DO_IFINTEGER	175
%token DO_IFCHAR	176
%token DO_IFLOGICAL	177
%token DO_IFSET	178
%token DO_IFSTRING	179
%token DO_IFLIST	180
%token DO_IFFLOAT	181
%token DO_IFFILE	182
%token DO_COND	183
%token DO_WHILE	184
%token DO_LINREC	185
%token DO_TAILREC	186
%token DO_BINREC	187
%token DO_GENREC	188
%token DO_CONDNESTREC	189
%token DO_CONDLINREC	190
%token DO_STEP	191
%token DO_FOLD	192
%token DO_MAP	193
%token DO_TIMES	194
%token DO_INFRA	195
%token DO_PRIMREC	196
%token DO_FILTER	197
%token DO_SPLIT	198
%token DO_SOME	199
%token DO_ALL	200
%token DO_TREESTEP	201
%token DO_TREEREC	202
%token DO_TREEGENREC	203
%token DO_HELP	204
%token DO_HELP1	205
%token DO_HELPDETAIL	206
%token DO_MANUAL	207
%token DO_HTML_MANUAL	208
%token DO_LATEX_MANUAL	209
%token DO_MANUAL_LIST	210
%token DO_SETTRACEGC	211
%token DO_SETAUTOPUT	212
%token DO_SETUNDEFERROR	213
%token DO_SETECHO	214
%token DO_GC	215
%token DO_SYSTEM	216
%token DO_GETENV	217
%token DO_ARGV	218
%token DO_ARGC	219
%token DO_MEMORYINDEX	220
%token DO_GET	221
%token DO_GETCH	222
%token DO_PUT	223
%token DO_PUTCH	224
%token DO_PUTCHARS	225
%token DO_INCLUDE	226
%token DO_ABORT	227
%token DO_QUIT	228
%token MODULE	229
%token <ent> JPRIVATE	230
%token JPUBLIC	231
%token JEQUAL	232
%token END	233
%token <num> Symbol	234
%token <num> BOOLEAN_	235
%token <num> CHAR_	236
%token <num> INTEGER_	237
%token <set> SET_	238
%token <str> STRING_	239
%token <lis> LIST_	240
%token <dbl> FLOAT_	241
%token <fil> FILE_	242
%token <ent> USR_	243
%token <proc> ANON_FUNCT_	244
%token <str> SYMBOL_	245

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
