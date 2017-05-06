%{
/*
    module  : lexer.l
    version : 1.11
    date    : 05/06/17
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "joy.h"
#include "symbol.h"

#ifdef FLEX_SCANNER
#define MAX_INCLUDE_DEPTH	10

int include_stack_ptr;
YY_BUFFER_STATE include_stack[MAX_INCLUDE_DEPTH];

static int input(void);
#endif

static void SkipComment(void)
{
    int ch;

    ch = input();
    do {
	while (ch != '*' && ch != EOF)
	    ch = input();
	if (ch == EOF)
	    execerror("no EOF", "SkipComment");
    } while ((ch = input()) != ')');
}

void new_buffer(void)
{
#ifdef FLEX_SCANNER
    if (include_stack_ptr >= MAX_INCLUDE_DEPTH)
	execerror("fewer include files", "redirect");
    include_stack[include_stack_ptr++] = YY_CURRENT_BUFFER;
    yy_switch_to_buffer(yy_create_buffer(yyin, YY_BUF_SIZE));
#endif
}

int old_buffer(void)
{
#ifdef FLEX_SCANNER
    if (--include_stack_ptr >= 0)
	yy_switch_to_buffer(include_stack[include_stack_ptr]);
#endif
    return 0;
}

#if defined(FLEX_SCANNER) && defined(_MSC_VER)
/*
    b->yy_is_interactive = file ? (isatty( fileno(file) ) > 0) : 0;
*/
int fileno(FILE *fp)
{
    return fp - stdin;
}

int isatty(int num)
{
    return !num;
}
#endif

int yyerror(char *str)
{
    fprintf(stderr, "%s\n", str);
    return 0;
}

#ifdef LEXDEBUG
static void allprint(int ch)
{
    if (isprint(ch))
	fputc(ch, yyout);
    else
	fprintf(yyout, "\\%03d", ch);
}

static void sprint(char *str)
{
    fprintf(yyout, "%s", str);
}
#endif
%}

%e		3000
%p		8000
%n		1000
%a		4000

firstchar	[!$%&*+,/:<=>?@A-Z\\^_`a-z|~]
nextchar	[-0-9=A-Z_a-z]
restchar	{firstchar}{nextchar}*
symbol		{restchar}(\.{restchar})*
escape		\\(["'\\btnvfr]|[01][0-9][0-9]|2[0-5][0-5])
character	'([^\\]|{escape})
string		\"([^"\\\n]|{escape})*\"
integer		(0|-?[1-9][0-9]*)
octal		0[1-7][0-7]*
hexal		0[Xx][0-9A-Fa-f]+
float		{integer}\.[0-9]+([Ee][-+]?[1-9][0-9]*)?
comment		"(*"
linecom		#.*

%%

LIBRA		|
DEFINE		|
IN		|
PUBLIC		{ return JPUBLIC; }
HIDE		|
PRIVATE		{ return JPRIVATE; }
"."		|
END		{ return END; }
MODULE		{ return MODULE; }
"=="		{ return JEQUAL; }

nothing		{ yylval.num = DO_NOTHING; return Symbol; }
false		{ yylval.num = 0; return BOOLEAN_; }
true		{ yylval.num = 1; return BOOLEAN_; }
maxint		{ yylval.num = MAXINT_; return INTEGER_; }
setsize		{ yylval.num = DO_SETSIZE; return Symbol; }
stack		{ yylval.num = DO_STACK; return Symbol; }
__symtabmax	{ yylval.num = DO_SYMTABMAX; return Symbol; }
__symtabindex	{ yylval.num = DO_SYMTABINDEX; return Symbol; }
__dump		{ yylval.num = DO_DUMP; return Symbol; }
conts		{ yylval.num = DO_CONTS; return Symbol; }
autoput		{ yylval.num = DO_AUTOPUT; return Symbol; }
undeferror	{ yylval.num = DO_UNDEFERROR; return Symbol; }
undefs		{ yylval.num = DO_UNDEFS; return Symbol; }
echo		{ yylval.num = DO_ECHO; return Symbol; }
clock		{ yylval.num = DO_CLOCK; return Symbol; }
time		{ yylval.num = DO_TIME; return Symbol; }
rand		{ yylval.num = DO_RAND; return Symbol; }
__memorymax	{ yylval.num = DO_MEMORYMAX; return Symbol; }
stdin		{ yylval.num = DO_STDIN; return Symbol; }
stdout		{ yylval.num = DO_STDOUT; return Symbol; }
stderr		{ yylval.num = DO_STDERR; return Symbol; }
id		{ yylval.num = DO_ID; return Symbol; }
dup		{ yylval.num = DO_DUP; return Symbol; }
swap		{ yylval.num = DO_SWAP; return Symbol; }
rollup		{ yylval.num = DO_ROLLUP; return Symbol; }
rolldown	{ yylval.num = DO_ROLLDOWN; return Symbol; }
rotate		{ yylval.num = DO_ROTATE; return Symbol; }
popd		{ yylval.num = DO_POPD; return Symbol; }
dupd		{ yylval.num = DO_DUPD; return Symbol; }
swapd		{ yylval.num = DO_SWAPD; return Symbol; }
rollupd		{ yylval.num = DO_ROLLUPD; return Symbol; }
rolldownd	{ yylval.num = DO_ROLLDOWND; return Symbol; }
rotated		{ yylval.num = DO_ROTATED; return Symbol; }
pop		{ yylval.num = DO_POP; return Symbol; }
choice		{ yylval.num = DO_CHOICE; return Symbol; }
or		{ yylval.num = DO_OR; return Symbol; }
xor		{ yylval.num = DO_XOR; return Symbol; }
and		{ yylval.num = DO_AND; return Symbol; }
not		{ yylval.num = DO_NOT; return Symbol; }
"+"		{ yylval.num = DO_PLUS; return Symbol; }
"-"		{ yylval.num = DO_MINUS; return Symbol; }
"*"		{ yylval.num = DO_MUL; return Symbol; }
"/"		{ yylval.num = DO_DIVIDE; return Symbol; }
rem		{ yylval.num = DO_REM; return Symbol; }
div		{ yylval.num = DO_DIV; return Symbol; }
sign		{ yylval.num = DO_SIGN; return Symbol; }
neg		{ yylval.num = DO_NEG; return Symbol; }
ord		{ yylval.num = DO_ORD; return Symbol; }
chr		{ yylval.num = DO_CHR; return Symbol; }
abs		{ yylval.num = DO_ABS; return Symbol; }
acos		{ yylval.num = DO_ACOS; return Symbol; }
asin		{ yylval.num = DO_ASIN; return Symbol; }
atan		{ yylval.num = DO_ATAN; return Symbol; }
atan2		{ yylval.num = DO_ATAN2; return Symbol; }
ceil		{ yylval.num = DO_CEIL; return Symbol; }
cos		{ yylval.num = DO_COS; return Symbol; }
cosh		{ yylval.num = DO_COSH; return Symbol; }
exp		{ yylval.num = DO_EXP; return Symbol; }
floor		{ yylval.num = DO_FLOOR; return Symbol; }
round		{ yylval.num = DO_ROUND; return Symbol; }
frexp		{ yylval.num = DO_FREXP; return Symbol; }
ldexp		{ yylval.num = DO_LDEXP; return Symbol; }
log		{ yylval.num = DO_LOG; return Symbol; }
log10		{ yylval.num = DO_LOG10; return Symbol; }
modf		{ yylval.num = DO_MODF; return Symbol; }
pow		{ yylval.num = DO_POW; return Symbol; }
sin		{ yylval.num = DO_SIN; return Symbol; }
sinh		{ yylval.num = DO_SINH; return Symbol; }
sqrt		{ yylval.num = DO_SQRT; return Symbol; }
tan		{ yylval.num = DO_TAN; return Symbol; }
tanh		{ yylval.num = DO_TANH; return Symbol; }
trunc		{ yylval.num = DO_TRUNC; return Symbol; }
localtime	{ yylval.num = DO_LOCALTIME; return Symbol; }
gmtime		{ yylval.num = DO_GMTIME; return Symbol; }
mktime		{ yylval.num = DO_MKTIME; return Symbol; }
strftime	{ yylval.num = DO_STRFTIME; return Symbol; }
strtol		{ yylval.num = DO_STRTOL; return Symbol; }
strtod		{ yylval.num = DO_STRTOD; return Symbol; }
format		{ yylval.num = DO_FORMAT; return Symbol; }
formatf		{ yylval.num = DO_FORMATF; return Symbol; }
srand		{ yylval.num = DO_SRAND; return Symbol; }
pred		{ yylval.num = DO_PRED; return Symbol; }
succ		{ yylval.num = DO_SUCC; return Symbol; }
max		{ yylval.num = DO_MAX; return Symbol; }
min		{ yylval.num = DO_MIN; return Symbol; }
fclose		{ yylval.num = DO_FCLOSE; return Symbol; }
feof		{ yylval.num = DO_FEOF; return Symbol; }
ferror		{ yylval.num = DO_FERROR; return Symbol; }
fflush		{ yylval.num = DO_FFLUSH; return Symbol; }
fget		{ yylval.num = DO_FGET; return Symbol; }
fgetch		{ yylval.num = DO_FGETCH; return Symbol; }
fgets		{ yylval.num = DO_FGETS; return Symbol; }
fopen		{ yylval.num = DO_FOPEN; return Symbol; }
fread		{ yylval.num = DO_FREAD; return Symbol; }
fwrite		{ yylval.num = DO_FWRITE; return Symbol; }
fremove		{ yylval.num = DO_FREMOVE; return Symbol; }
frename		{ yylval.num = DO_FRENAME; return Symbol; }
filetime	{ yylval.num = DO_FILETIME; return Symbol; }
fput		{ yylval.num = DO_FPUT; return Symbol; }
fputch		{ yylval.num = DO_FPUTCH; return Symbol; }
fputchars	{ yylval.num = DO_FPUTCHARS; return Symbol; }
fputstring	{ yylval.num = DO_FPUTCHARS; return Symbol; }
fseek		{ yylval.num = DO_FSEEK; return Symbol; }
ftell		{ yylval.num = DO_FTELL; return Symbol; }
unstack		{ yylval.num = DO_UNSTACK; return Symbol; }
cons		{ yylval.num = DO_CONS; return Symbol; }
swons		{ yylval.num = DO_SWONS; return Symbol; }
first		{ yylval.num = DO_FIRST; return Symbol; }
rest		{ yylval.num = DO_REST; return Symbol; }
compare		{ yylval.num = DO_COMPARE; return Symbol; }
at		{ yylval.num = DO_AT; return Symbol; }
of		{ yylval.num = DO_OF; return Symbol; }
size		{ yylval.num = DO_SIZE; return Symbol; }
opcase		{ yylval.num = DO_OPCASE; return Symbol; }
case		{ yylval.num = DO_CASE; return Symbol; }
uncons		{ yylval.num = DO_UNCONS; return Symbol; }
unswons		{ yylval.num = DO_UNSWONS; return Symbol; }
drop		{ yylval.num = DO_DROP; return Symbol; }
take		{ yylval.num = DO_TAKE; return Symbol; }
concat		{ yylval.num = DO_CONCAT; return Symbol; }
enconcat	{ yylval.num = DO_ENCONCAT; return Symbol; }
name		{ yylval.num = DO_NAME; return Symbol; }
intern		{ yylval.num = DO_INTERN; return Symbol; }
body		{ yylval.num = DO_BODY; return Symbol; }
null		{ yylval.num = DO_NULL; return Symbol; }
small		{ yylval.num = DO_SMALL; return Symbol; }
">="		{ yylval.num = DO_GEQL; return Symbol; }
">"		{ yylval.num = DO_GREATER; return Symbol; }
"<="		{ yylval.num = DO_LEQL; return Symbol; }
"<"		{ yylval.num = DO_LESS; return Symbol; }
"!="		{ yylval.num = DO_NEQL; return Symbol; }
"="		{ yylval.num = DO_EQL; return Symbol; }
equal		{ yylval.num = DO_EQUAL; return Symbol; }
has		{ yylval.num = DO_HAS; return Symbol; }
in		{ yylval.num = DO_IN; return Symbol; }
index		{ yylval.num = DO_INDEX; return Symbol; }
sametype	{ yylval.num = DO_SAMETYPE; return Symbol; }
casting		{ yylval.num = DO_CASTING; return Symbol; }
integer		{ yylval.num = DO_INTEGER; return Symbol; }
char		{ yylval.num = DO_CHAR; return Symbol; }
logical		{ yylval.num = DO_LOGICAL; return Symbol; }
set		{ yylval.num = DO_SET; return Symbol; }
string		{ yylval.num = DO_STRING; return Symbol; }
list		{ yylval.num = DO_LIST; return Symbol; }
leaf		{ yylval.num = DO_LEAF; return Symbol; }
user		{ yylval.num = DO_USER; return Symbol; }
float		{ yylval.num = DO_FLOAT; return Symbol; }
file		{ yylval.num = DO_FILE; return Symbol; }
i		{ yylval.num = DO_I; return Symbol; }
x		{ yylval.num = DO_X; return Symbol; }
dip		{ yylval.num = DO_DIP; return Symbol; }
app1		{ yylval.num = DO_APP1; return Symbol; }
app11		{ yylval.num = DO_APP11; return Symbol; }
app12		{ yylval.num = DO_APP12; return Symbol; }
construct	{ yylval.num = DO_CONSTRUCT; return Symbol; }
nullary		{ yylval.num = DO_NULLARY; return Symbol; }
unary		{ yylval.num = DO_UNARY; return Symbol; }
unary2		{ yylval.num = DO_UNARY2; return Symbol; }
unary3		{ yylval.num = DO_UNARY3; return Symbol; }
unary4		{ yylval.num = DO_UNARY4; return Symbol; }
app2		{ yylval.num = DO_UNARY2; return Symbol; }
app3		{ yylval.num = DO_UNARY3; return Symbol; }
app4		{ yylval.num = DO_UNARY4; return Symbol; }
binary		{ yylval.num = DO_BINARY; return Symbol; }
ternary		{ yylval.num = DO_TERNARY; return Symbol; }
cleave		{ yylval.num = DO_CLEAVE; return Symbol; }
branch		{ yylval.num = DO_BRANCH; return Symbol; }
ifte		{ yylval.num = DO_IFTE; return Symbol; }
ifinteger	{ yylval.num = DO_IFINTEGER; return Symbol; }
ifchar		{ yylval.num = DO_IFCHAR; return Symbol; }
iflogical	{ yylval.num = DO_IFLOGICAL; return Symbol; }
ifset		{ yylval.num = DO_IFSET; return Symbol; }
ifstring	{ yylval.num = DO_IFSTRING; return Symbol; }
iflist		{ yylval.num = DO_IFLIST; return Symbol; }
iffloat		{ yylval.num = DO_IFFLOAT; return Symbol; }
iffile		{ yylval.num = DO_IFFILE; return Symbol; }
cond		{ yylval.num = DO_COND; return Symbol; }
while		{ yylval.num = DO_WHILE; return Symbol; }
linrec		{ yylval.num = DO_LINREC; return Symbol; }
tailrec		{ yylval.num = DO_TAILREC; return Symbol; }
binrec		{ yylval.num = DO_BINREC; return Symbol; }
genrec		{ yylval.num = DO_GENREC; return Symbol; }
condnestrec	{ yylval.num = DO_CONDNESTREC; return Symbol; }
condlinrec	{ yylval.num = DO_CONDLINREC; return Symbol; }
step		{ yylval.num = DO_STEP; return Symbol; }
fold		{ yylval.num = DO_FOLD; return Symbol; }
map		{ yylval.num = DO_MAP; return Symbol; }
times		{ yylval.num = DO_TIMES; return Symbol; }
infra		{ yylval.num = DO_INFRA; return Symbol; }
primrec		{ yylval.num = DO_PRIMREC; return Symbol; }
filter		{ yylval.num = DO_FILTER; return Symbol; }
split		{ yylval.num = DO_SPLIT; return Symbol; }
some		{ yylval.num = DO_SOME; return Symbol; }
all		{ yylval.num = DO_ALL; return Symbol; }
treestep	{ yylval.num = DO_TREESTEP; return Symbol; }
treerec		{ yylval.num = DO_TREEREC; return Symbol; }
treegenrec	{ yylval.num = DO_TREEGENREC; return Symbol; }
help		{ yylval.num = DO_HELP; return Symbol; }
_help		{ yylval.num = DO_HELP1; return Symbol; }
helpdetail	{ yylval.num = DO_HELPDETAIL; return Symbol; }
manual		{ yylval.num = DO_MANUAL; return Symbol; }
__html_manual	{ yylval.num = DO_HTML_MANUAL; return Symbol; }
__latex_manual	{ yylval.num = DO_LATEX_MANUAL; return Symbol; }
__manual_list	{ yylval.num = DO_MANUAL_LIST; return Symbol; }
__settracegc	{ yylval.num = DO_SETTRACEGC; return Symbol; }
setautoput	{ yylval.num = DO_SETAUTOPUT; return Symbol; }
setundeferror	{ yylval.num = DO_SETUNDEFERROR; return Symbol; }
setecho		{ yylval.num = DO_SETECHO; return Symbol; }
gc		{ yylval.num = DO_GC; return Symbol; }
system		{ yylval.num = DO_SYSTEM; return Symbol; }
getenv		{ yylval.num = DO_GETENV; return Symbol; }
argv		{ yylval.num = DO_ARGV; return Symbol; }
argc		{ yylval.num = DO_ARGC; return Symbol; }
__memoryindex	{ yylval.num = DO_MEMORYINDEX; return Symbol; }
get		{ yylval.num = DO_GET; return Symbol; }
getch		{ yylval.num = DO_GETCH; return Symbol; }
put		{ yylval.num = DO_PUT; return Symbol; }
putch		{ yylval.num = DO_PUTCH; return Symbol; }
putchars	{ yylval.num = DO_PUTCHARS; return Symbol; }
include		{ yylval.num = DO_INCLUDE; return Symbol; }
abort		{ yylval.num = DO_ABORT; return Symbol; }
quit		{ yylval.num = DO_QUIT; return Symbol; }

{symbol}	{ yylval.ent = lookup(yytext); return USR_; }
{character}	{ yylval.num = ChrVal(yytext + 1); return CHAR_; }
{string}	{ yylval.str = StrVal(yytext + 1); return STRING_; }
{integer}	|
{octal}		|
{hexal}		{ yylval.num = strtol(yytext, 0, 0); return INTEGER_; }
{float}		{ yylval.dbl = atof(yytext); return FLOAT_; }
{comment}	SkipComment();
{linecom}	|
[ \t\n\r]+	;
^\$.*		system(yytext + 1);
^\%INCLUDE.*	include(DelSpace(yytext + 8));
^\%PUT.*	fprintf(stderr, "%s\n", yytext + 4);
.		return yytext[0];
