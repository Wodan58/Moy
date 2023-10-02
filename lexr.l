%{
/*
    module  : lexr.l
    version : 1.12
    date    : 10/02/23
*/
#include "globals.h"

#define YY_DECL		int my_yylex(pEnv env)
#define YY_NO_UNPUT

#define OUT_OF_COM	0
#define WITHIN_COM	1
#define LEAVE_COMM	2

char line[INPLINEMAX + 1];
static int linenum;

static int include_stack_ptr;
static YY_BUFFER_STATE include_stack[INPSTACKMAX];

/*
    Add a character to the current input line, upto INPLINEMAX.
*/
static void addline(int ch)
{
    static int linepos;

    if (linepos >= INPLINEMAX)
	return;
    if (ch == '\n') {
	linepos = 0; /* reset linepos */
	return;
    }
    line[linepos++] = ch;
    line[linepos] = 0;
}

/*
    Echo an input line to stdout
*/
static void putline(pEnv env, char *str, int leng, int status)
{
    int i, target;

    for (i = 0; i < leng; i++)
	addline(str[i]);
    if (!env->echoflag)
	return;
    i = linenum;
    target = status == LEAVE_COMM ? yylineno : yylineno - 1;
    if (i)
	for (; i < target; i++) {
	    if (env->echoflag > 2)
		printf("%4d", i);
	    putchar('\n');		/* fill in missing lines */
	}
    if (linenum <= target || target == 1) {
	if (env->echoflag > 2)
	    printf("%4d", target);
	if (env->echoflag > 1)
	    putchar('\t');
	printf("%s\n", line);		/* include newline */
    }
    linenum = target + 1;
}

PUBLIC void new_buffer(void)
{
    include_stack[include_stack_ptr++] = YY_CURRENT_BUFFER;
    yy_switch_to_buffer(yy_create_buffer(yyin, YY_BUF_SIZE));
    yylineno = 1; /* restart with line 1 */
}

PUBLIC void old_buffer(int num)
{
    if (--include_stack_ptr < 0)
	include_stack_ptr = 0;
    if (include_stack[include_stack_ptr])
	yy_switch_to_buffer(include_stack[include_stack_ptr]);
    yylineno = num; /* restart old file */
    linenum = num + 1;
}

/* Update the column positions, each time some text is matched. */
#define YY_USER_ACTION	do { yylloc.first_column = yylloc.last_column; \
			     yylloc.last_column += yyleng; } while (0);
%}

%option		yylineno
%x		COMMENT

firstchar	[!$%&*+,/:<=>?@A-Z\\^_`a-z|~]
nextchar	[-0-9=A-Z_a-z]
restchar	({firstchar}{nextchar}*|[-]([-=A-Z_a-z]{nextchar}*)?)
symbol		{restchar}(\.{restchar})*
escape		\\(["'\\btnvfr]|[01][0-9][0-9]|2[0-5][0-5])
character	'([^\\]|{escape})
string		\"([^"\\\n]|{escape})*\"
integer		-?(0|[1-9][0-9]*)
octal		0[1-7][0-7]*
hexal		0[Xx][0-9A-Fa-f]+
float		{integer}\.[0-9]+([Ee][-+]?[1-9][0-9]*)?
comment		"(*"
linecom		#.*

%%

<<EOF>>		quit_(env);
<COMMENT>"*)"	{ putline(env, "*)", 2, LEAVE_COMM); BEGIN INITIAL; }
<COMMENT>.	addline(yytext[0]);
<COMMENT>\n	{ putline(env, "\n", 1, WITHIN_COM); }

[\n]+.*\n	{ int i = 0; putline(env, yytext, yyleng, OUT_OF_COM);
		  while (yytext[i] == '\n') i++; yyless(i); /* reset columns */
		  yylloc.first_column = yylloc.last_column = 0; }
LIBRA[ \t]*	|
DEFINE[ \t]*	|
IN[ \t]*	|
PUBLIC[ \t]*	return JPUBLIC;
HIDE[ \t]*	|
PRIVATE[ \t]*	return JPRIVATE;
"."[ \t]*	|
END[ \t]*	return END;
MODULE[ \t]*	return MODULE;
"=="[ \t]*	return EQDEF;

{character}	{ yylval.num = ChrVal(yytext + 1); return CHAR_; }
{octal}		|
{hexal}		{ yylval.num = strtoll(yytext, 0, 0); if (yylval.num == MAXINT)
		{ yylval.dbl = strtod(yytext, 0); return FLOAT_; }
		  return INTEGER_; }
{integer}	{ yylval.num = strtoll(yytext + (yytext[0] == '-' ? 1 : 0),
		  0, 0);
		  if (yylval.num == MAXINT) { yylval.str = GC_strdup(yytext);
		  return BIGNUM_; }
		  if (yytext[0] == '-') yylval.num = -yylval.num;
		  return INTEGER_; }
{float}		{ yylval.dbl = strtod(yytext, 0); return FLOAT_; }
{string}	{ yylval.str = StrVal(yytext + 1); return STRING_; }
{symbol}	{ yylval.str = GC_strdup(yytext); return USR_; }
{comment}	{ addline('('); addline('*'); BEGIN COMMENT; }
{linecom}	{ /* default to ECHO */ }
^\$.*		system(yytext + 1);
^\%INCLUDE.*	include(env, DelSpace(yytext + 8), 1);
^\%PUT.*	{ fflush(stdout); fprintf(stderr, "%s\n", yytext + 4); }
^\%LISTING.*	env->echoflag = atoi(yytext + 8);
^\%TRACE.*	env->debugging = atoi(yytext + 6);
[ \b\t\n\v\f\r]	;
[;[\]{}]	|
.		return yytext[0];

%%

PUBLIC int get_char(void)
{
    int ch;

    while ((ch = input()) <= ' ')
	;
    return ch;
}
