%{
/*
    module  : lexer.l
    version : 1.3
    date    : 09/09/16
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include "memory.h"
#include "globals1.h"

#ifdef YYLMAX
#undef YYLMAX
#define YYLMAX	2000
#endif

static int inside_global;

int yylook(void), yywrap(void), yyback(int *, int);

int yyerror(char *str)
{
    fprintf(stderr, "%s (%d)\n", str, yylval.num);
    return 0;
}

static char *DelSpace(char *str)
{
    int i;

    for (i = strlen(str) - 1; i >= 0; i--)
	if (isspace((int) str[i]))
	    str[i] = 0;
	else
	    break;
    while (isspace((int) *str))
	str++;
    return str;
}

#ifdef LEXDEBUG
void allprint(int ch)
{
    if (isprint(ch))
	fputc(ch, yyout);
    else
	fprintf(yyout, "\\%03d", ch);
}

void sprint(char *str)
{
    fprintf(yyout, "%s", str);
}
#endif

int isatty(int num)
{
    if (num)
	num = 0;
    return 1;
}
%}

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
linecom		#.*
comment		"(*"")"*([^*)]|[^*]")"|"*"[^)])*"*"*"*)"

%%

LIBRA		|
DEFINE		|
IN		|
PUBLIC		{ inside_global++; inside_definition = 1; return JPUBLIC; }
HIDE		|
PRIVATE		{ inside_definition = 1; return JPRIVATE; }
"."		|
END		{ if (inside_global) inside_global--; inside_definition =
		  inside_global > 0; return END; }
MODULE		{ inside_definition = 1; return MODULE; }
"=="		{ return JEQUAL; }

false		{ yylval.num = 0; return BOOLEAN_; }
true		{ yylval.num = 1; return BOOLEAN_; }
maxint		{ yylval.num = _MAXINT_; return INTEGER_; }
setsize		{ yylval.num = SETSIZE; return Symbol; }
stack		{ yylval.num = STACK; return Symbol; }
__symtabmax	{ yylval.num = __SYMTABMAX; return Symbol; }
__symtabindex	{ yylval.num = __SYMTABINDEX; return Symbol; }
__dump		{ yylval.num = __DUMP; return Symbol; }
conts		{ yylval.num = CONTS; return Symbol; }
autoput		{ yylval.num = AUTOPUT; return Symbol; }
undeferror	{ yylval.num = UNDEFERROR; return Symbol; }
undefs		{ yylval.num = UNDEFS; return Symbol; }
echo		{ yylval.num = ECHO_; return Symbol; }
clock		{ yylval.num = CLOCK; return Symbol; }
time		{ yylval.num = TIME; return Symbol; }
rand		{ yylval.num = RAND; return Symbol; }
__memorymax	{ yylval.num = __MEMORYMAX; return Symbol; }
stdin		{ yylval.num = STDIN; return Symbol; }
stdout		{ yylval.num = STDOUT; return Symbol; }
stderr		{ yylval.num = STDERR; return Symbol; }
id		{ yylval.num = ID; return Symbol; }
dup		{ yylval.num = DUP; return Symbol; }
swap		{ yylval.num = SWAP; return Symbol; }
rollup		{ yylval.num = ROLLUP; return Symbol; }
rolldown	{ yylval.num = ROLLDOWN; return Symbol; }
rotate		{ yylval.num = ROTATE; return Symbol; }
popd		{ yylval.num = POPD; return Symbol; }
dupd		{ yylval.num = DUPD; return Symbol; }
swapd		{ yylval.num = SWAPD; return Symbol; }
rollupd		{ yylval.num = ROLLUPD; return Symbol; }
rolldownd	{ yylval.num = ROLLDOWND; return Symbol; }
rotated		{ yylval.num = ROTATED; return Symbol; }
pop		{ yylval.num = POP; return Symbol; }
choice		{ yylval.num = CHOICE; return Symbol; }
or		{ yylval.num = OR; return Symbol; }
xor		{ yylval.num = XOR; return Symbol; }
and		{ yylval.num = AND; return Symbol; }
not		{ yylval.num = NOT; return Symbol; }
"+"		{ yylval.num = PLUS; return Symbol; }
"-"		{ yylval.num = MINUS; return Symbol; }
"*"		{ yylval.num = MUL; return Symbol; }
"/"		{ yylval.num = DIVIDE; return Symbol; }
rem		{ yylval.num = REM; return Symbol; }
div		{ yylval.num = DIV; return Symbol; }
sign		{ yylval.num = SIGN; return Symbol; }
neg		{ yylval.num = NEG; return Symbol; }
ord		{ yylval.num = ORD; return Symbol; }
chr		{ yylval.num = CHR; return Symbol; }
abs		{ yylval.num = ABS; return Symbol; }
acos		{ yylval.num = ACOS; return Symbol; }
asin		{ yylval.num = ASIN; return Symbol; }
atan		{ yylval.num = ATAN; return Symbol; }
atan2		{ yylval.num = ATAN2; return Symbol; }
ceil		{ yylval.num = CEIL; return Symbol; }
cos		{ yylval.num = COS; return Symbol; }
cosh		{ yylval.num = COSH; return Symbol; }
exp		{ yylval.num = EXP; return Symbol; }
floor		{ yylval.num = FLOOR; return Symbol; }
round		{ yylval.num = ROUND; return Symbol; }
frexp		{ yylval.num = FREXP; return Symbol; }
ldexp		{ yylval.num = LDEXP; return Symbol; }
log		{ yylval.num = LOG; return Symbol; }
log10		{ yylval.num = LOG10; return Symbol; }
modf		{ yylval.num = MODF; return Symbol; }
pow		{ yylval.num = POW; return Symbol; }
sin		{ yylval.num = SIN; return Symbol; }
sinh		{ yylval.num = SINH; return Symbol; }
sqrt		{ yylval.num = SQRT; return Symbol; }
tan		{ yylval.num = TAN; return Symbol; }
tanh		{ yylval.num = TANH; return Symbol; }
trunc		{ yylval.num = TRUNC; return Symbol; }
localtime	{ yylval.num = LOCALTIME; return Symbol; }
gmtime		{ yylval.num = GMTIME; return Symbol; }
mktime		{ yylval.num = MKTIME; return Symbol; }
strftime	{ yylval.num = STRFTIME; return Symbol; }
strtol		{ yylval.num = STRTOL; return Symbol; }
strtod		{ yylval.num = STRTOD; return Symbol; }
format		{ yylval.num = FORMAT; return Symbol; }
formatf		{ yylval.num = FORMATF; return Symbol; }
srand		{ yylval.num = SRAND; return Symbol; }
pred		{ yylval.num = PRED; return Symbol; }
succ		{ yylval.num = SUCC; return Symbol; }
max		{ yylval.num = MAX; return Symbol; }
min		{ yylval.num = MIN; return Symbol; }
fclose		{ yylval.num = FCLOSE; return Symbol; }
feof		{ yylval.num = FEOF; return Symbol; }
ferror		{ yylval.num = FERROR; return Symbol; }
fflush		{ yylval.num = FFLUSH; return Symbol; }
fget		{ yylval.num = FGET; return Symbol; }
fgetch		{ yylval.num = FGETCH; return Symbol; }
fgets		{ yylval.num = FGETS; return Symbol; }
fopen		{ yylval.num = FOPEN; return Symbol; }
fread		{ yylval.num = FREAD; return Symbol; }
fwrite		{ yylval.num = FWRITE; return Symbol; }
fremove		{ yylval.num = FREMOVE; return Symbol; }
frename		{ yylval.num = FRENAME; return Symbol; }
filetime	{ yylval.num = FILETIME; return Symbol; }
fput		{ yylval.num = FPUT; return Symbol; }
fputch		{ yylval.num = FPUTCH; return Symbol; }
fputchars	{ yylval.num = FPUTCHARS; return Symbol; }
fputstring	{ yylval.num = FPUTCHARS; return Symbol; }
fseek		{ yylval.num = FSEEK; return Symbol; }
ftell		{ yylval.num = FTELL; return Symbol; }
unstack		{ yylval.num = UNSTACK; return Symbol; }
cons		{ yylval.num = CONS; return Symbol; }
swons		{ yylval.num = SWONS; return Symbol; }
first		{ yylval.num = FIRST; return Symbol; }
rest		{ yylval.num = REST; return Symbol; }
compare		{ yylval.num = COMPARE; return Symbol; }
at		{ yylval.num = AT; return Symbol; }
of		{ yylval.num = OF; return Symbol; }
size		{ yylval.num = SIZE; return Symbol; }
opcase		{ yylval.num = OPCASE; return Symbol; }
case		{ yylval.num = CASE; return Symbol; }
uncons		{ yylval.num = UNCONS; return Symbol; }
unswons		{ yylval.num = UNSWONS; return Symbol; }
drop		{ yylval.num = DROP; return Symbol; }
take		{ yylval.num = TAKE; return Symbol; }
concat		{ yylval.num = CONCAT; return Symbol; }
enconcat	{ yylval.num = ENCONCAT; return Symbol; }
name		{ yylval.num = NAME; return Symbol; }
intern		{ yylval.num = INTERN; return Symbol; }
body		{ yylval.num = BODY; return Symbol; }
null		{ yylval.num = NULL_; return Symbol; }
small		{ yylval.num = SMALL; return Symbol; }
">="		{ yylval.num = GEQL; return Symbol; }
">"		{ yylval.num = GREATER; return Symbol; }
"<="		{ yylval.num = LEQL; return Symbol; }
"<"		{ yylval.num = LESS; return Symbol; }
"!="		{ yylval.num = NEQL; return Symbol; }
"="		{ yylval.num = EQL; return Symbol; }
equal		{ yylval.num = EQUAL; return Symbol; }
has		{ yylval.num = HAS; return Symbol; }
in		{ yylval.num = IN; return Symbol; }
sametype	{ yylval.num = SAMETYPE; return Symbol; }
casting		{ yylval.num = CASTING; return Symbol; }
integer		{ yylval.num = INTEGER; return Symbol; }
char		{ yylval.num = CHAR; return Symbol; }
logical		{ yylval.num = LOGICAL; return Symbol; }
set		{ yylval.num = SET; return Symbol; }
string		{ yylval.num = STRING; return Symbol; }
list		{ yylval.num = LIST; return Symbol; }
leaf		{ yylval.num = LEAF; return Symbol; }
user		{ yylval.num = USER; return Symbol; }
float		{ yylval.num = FLOAT; return Symbol; }
file		{ yylval.num = _FILE_; return Symbol; }
i		{ yylval.num = I; return Symbol; }
x		{ yylval.num = X; return Symbol; }
dip		{ yylval.num = DIP; return Symbol; }
app1		{ yylval.num = APP1; return Symbol; }
app11		{ yylval.num = APP11; return Symbol; }
app12		{ yylval.num = APP12; return Symbol; }
construct	{ yylval.num = CONSTRUCT; return Symbol; }
nullary		{ yylval.num = NULLARY; return Symbol; }
unary		{ yylval.num = UNARY; return Symbol; }
unary2		{ yylval.num = UNARY2; return Symbol; }
unary3		{ yylval.num = UNARY3; return Symbol; }
unary4		{ yylval.num = UNARY4; return Symbol; }
app2		{ yylval.num = UNARY2; return Symbol; }
app3		{ yylval.num = UNARY3; return Symbol; }
app4		{ yylval.num = UNARY4; return Symbol; }
binary		{ yylval.num = BINARY; return Symbol; }
ternary		{ yylval.num = TERNARY; return Symbol; }
cleave		{ yylval.num = CLEAVE; return Symbol; }
branch		{ yylval.num = BRANCH; return Symbol; }
ifte		{ yylval.num = IFTE; return Symbol; }
ifinteger	{ yylval.num = IFINTEGER; return Symbol; }
ifchar		{ yylval.num = IFCHAR; return Symbol; }
iflogical	{ yylval.num = IFLOGICAL; return Symbol; }
ifset		{ yylval.num = IFSET; return Symbol; }
ifstring	{ yylval.num = IFSTRING; return Symbol; }
iflist		{ yylval.num = IFLIST; return Symbol; }
iffloat		{ yylval.num = IFFLOAT; return Symbol; }
iffile		{ yylval.num = IFFILE; return Symbol; }
cond		{ yylval.num = COND; return Symbol; }
while		{ yylval.num = WHILE; return Symbol; }
linrec		{ yylval.num = LINREC; return Symbol; }
tailrec		{ yylval.num = TAILREC; return Symbol; }
binrec		{ yylval.num = BINREC; return Symbol; }
genrec		{ yylval.num = GENREC; return Symbol; }
condnestrec	{ yylval.num = CONDNESTREC; return Symbol; }
condlinrec	{ yylval.num = CONDLINREC; return Symbol; }
step		{ yylval.num = STEP; return Symbol; }
fold		{ yylval.num = FOLD; return Symbol; }
map		{ yylval.num = MAP; return Symbol; }
times		{ yylval.num = TIMES; return Symbol; }
infra		{ yylval.num = INFRA; return Symbol; }
primrec		{ yylval.num = PRIMREC; return Symbol; }
filter		{ yylval.num = FILTER; return Symbol; }
split		{ yylval.num = SPLIT; return Symbol; }
some		{ yylval.num = SOME; return Symbol; }
all		{ yylval.num = ALL; return Symbol; }
treestep	{ yylval.num = TREESTEP; return Symbol; }
treerec		{ yylval.num = TREEREC; return Symbol; }
treegenrec	{ yylval.num = TREEGENREC; return Symbol; }
help		{ yylval.num = HELP; return Symbol; }
_help		{ yylval.num = _HELP; return Symbol; }
helpdetail	{ yylval.num = HELPDETAIL; return Symbol; }
manual		{ yylval.num = MANUAL; return Symbol; }
__html_manual	{ yylval.num = __HTML_MANUAL; return Symbol; }
__latex_manual	{ yylval.num = __LATEX_MANUAL; return Symbol; }
__manual_list	{ yylval.num = __MANUAL_LIST; return Symbol; }
__settracegc	{ yylval.num = __SETTRACEGC; return Symbol; }
setautoput	{ yylval.num = SETAUTOPUT; return Symbol; }
setundeferror	{ yylval.num = SETUNDEFERROR; return Symbol; }
setecho		{ yylval.num = SETECHO; return Symbol; }
gc		{ yylval.num = GC; return Symbol; }
system		{ yylval.num = SYSTEM; return Symbol; }
getenv		{ yylval.num = GETENV; return Symbol; }
argv		{ yylval.num = ARGV; return Symbol; }
argc		{ yylval.num = ARGC; return Symbol; }
__memoryindex	{ yylval.num = __MEMORYINDEX; return Symbol; }
get		{ yylval.num = GET; return Symbol; }
getch		{ yylval.num = GETCH; return Symbol; }
put		{ yylval.num = PUT; return Symbol; }
putch		{ yylval.num = PUTCH; return Symbol; }
putchars	{ yylval.num = PUTCHARS; return Symbol; }
include		{ yylval.num = INCLUDE; return Symbol; }
abort		{ yylval.num = ABORT; return Symbol; }
quit		{ yylval.num = QUIT; return Symbol; }

{symbol}	{ yylval.str = strdup(yytext); return SYMBOL_; }
{character}	{ yylval.num = ChrVal(yytext + 1); return CHAR_; }
{string}	{ yylval.str = StrVal(yytext + 1); return STRING_; }
{integer}	|
{octal}		|
{hexal}		{ yylval.num = strtol(yytext, 0, 0); return INTEGER_; }
{float}		{ yylval.dbl = atof(yytext); return FLOAT_; }
{linecom}	|
{comment}	|
[ \t\n\r]+	;
^\$.*		system(yytext + 1);
^\%INCLUDE.*	include(DelSpace(yytext + 8));
^\%PUT.*	fprintf(stderr, "%s\n", yytext + 4);
.		return yytext[0];
