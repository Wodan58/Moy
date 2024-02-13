%{
/*
    module  : lexr.l
    version : 1.27
    date    : 02/13/24
*/
#include "globals.h"

#ifdef _MSC_VER
#define YY_NO_UNISTD_H
#endif

#define YY_DECL		int my_yylex(pEnv env)
#define YY_NO_UNPUT

#define OUT_OF_COM	0
#define WITHIN_COM	1
#define LEAVE_COMM	2
#define MAX_FILLER	3	/* allow max. three empty lines */

char line[INPLINEMAX + 1];
static int linenum, linepos;

static int include_stack_ptr;
static YY_BUFFER_STATE include_stack[INPSTACKMAX];

/*
    Add a character to the current input line, upto INPLINEMAX.
*/
static void addline(int ch)
{
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
    if (i && target - i < MAX_FILLER)
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
    yylineno = 1;			/* restart with line 1 */
    linepos = 0;			/* start at position 0 */
}

PUBLIC void old_buffer(int num)
{
    if (--include_stack_ptr < 0)
	include_stack_ptr = 0;
    if (include_stack[include_stack_ptr])
	yy_switch_to_buffer(include_stack[include_stack_ptr]);
    yylineno = num;			/* restart old file */
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

<<EOF>>		{ quit_(env); }
<COMMENT>"*)"	{ putline(env, "*)", 2, LEAVE_COMM); BEGIN INITIAL; }
<COMMENT>.	{ addline(yytext[0]); }
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

{character}	{ yylval.num = ChrVal(env, yytext + 1); return CHAR_; }
{octal}		|
{hexal}		{ yylval.num = strtoll(yytext, 0, 0); if (yylval.num == MAXINT)
		{ yylval.dbl = strtod(yytext, 0); return FLOAT_; }
		  return INTEGER_; }
{integer}	{ yylval.num = strtoll(yytext + (yytext[0] == '-' ? 1 : 0),
		  0, 0);
		  if (yylval.num == MAXINT) {
#ifdef USE_BIGNUM_ARITHMETIC
			yylval.str = GC_strdup(yytext);
			return BIGNUM_;
#else
			yylval.dbl = strtod(yytext, 0);
			return FLOAT_;
#endif
		  }
		  if (yytext[0] == '-') yylval.num = -yylval.num;
		  return INTEGER_;
		}
{float}		{ yylval.dbl = strtod(yytext, 0); return FLOAT_; }
{string}	{ yylval.str = StrVal(env, yytext + 1); return STRING_; }
{symbol}	{ yylval.str = GC_strdup(yytext); return USR_; }
{comment}	{ addline('('); addline('*'); BEGIN COMMENT; }
{linecom}	{ /* default to ECHO */ }
^\$.*		{ int rv; if (!env->ignore) { rv = system(yytext + 1); if (rv) {
		  fflush(stdout); fprintf(stderr, "system: %d\n", rv); } } }
[ \b\t\n\v\f\r]	;
[;[\]{}]	|
.		return yytext[0];

%%

/*
    Supporting getch, reading from the stack of input files, like get.
*/
PUBLIC int get_input(void)
{
    return input();
}
