%{
/*
    module  : lexer.l
    version : 1.31
    date    : 06/22/22
*/
#include "globals.h"

#define YY_DECL		int yylex(pEnv env)

#define OUT_OF_COM	0
#define WITHIN_COM	1
#define LEAVE_COMM	2

char line[INPLINEMAX + 1];
static int moy_echo, comment, linenum;

static int include_stack_ptr;
static YY_BUFFER_STATE include_stack[INPSTACKMAX];

/* requires -std=c99 */
static int input(void);

static void SkipComment(void)
{
    int ch;

    ch = input();
    do {
	while (ch != '*' && ch != EOF)
	    ch = input();
	if (ch == EOF)
	    break;
    } while ((ch = input()) != ')' && ch != EOF);
}

int getnextchar(void)
{
    int ch;

    while ((ch = input()) <= ' ')
	if (ch == EOF)
	    break;
    return ch;
}

int getechoflag(void)
{
    return moy_echo;
}

void setechoflag(int flag)
{
    moy_echo = flag;
}

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

static void putline(char *str, int leng, int status)
{
    static int first;
    int i, start, finish;

    start = strstr(str, "(*") != 0;
    finish = strstr(str, "*)") != 0;
    comment = start && finish;
    if (status == OUT_OF_COM) {
	first = 0;
	if (comment)
	    goto skip;
	if (start) {
	    addline('(');
	    addline('*');
	    return;			/* add start of comment */
	}
    } else if (!first) {
	first = 1;
	if (strstr(line, "(*"))
	    goto skip;
	addline('(');			/* add start of comment */
	addline('*');
    }
skip:
    for (i = 0; i < leng; i++)
	addline(str[i]);
    if (!moy_echo)
	return;
    i = linenum;
    if (status == LEAVE_COMM)
	linenum = yylineno;		/* yylineno should not be corrected */
    else
	linenum = yylineno - 1;
    fflush(stdout);			/* synchronise stdout and stderr */
    if (i)
	for (; i < linenum; i++) {
	    if (moy_echo > 2)
		fprintf(stderr, "%4d", i);
	    fprintf(stderr, "\n");	/* fill in missing lines */
	}
    if (moy_echo > 2)
	fprintf(stderr, "%4d", linenum);
    if (moy_echo > 1)
	fprintf(stderr, "\t");
    fprintf(stderr, "%s\n", line);	/* include newline */
    line[0] = 0;			/* invalidate line */
    linenum++;
}

void new_buffer(pEnv env)
{
    if (include_stack_ptr >= INPSTACKMAX)
	execerror(env, "fewer include files", "redirect");
    include_stack[include_stack_ptr++] = YY_CURRENT_BUFFER;
    yy_switch_to_buffer(yy_create_buffer(yyin, YY_BUF_SIZE));
}

int old_buffer(void)
{
    linenum = yylineno + 1;
    if (--include_stack_ptr >= 0)
	yy_switch_to_buffer(include_stack[include_stack_ptr]);
    return 0;
}
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

<<EOF>>		{ do_quit(env); }

<COMMENT>"*)"	{ putline("*)", 2, LEAVE_COMM); BEGIN INITIAL; }
<COMMENT>.	addline(yytext[0]);
<COMMENT>\n	putline("\n", 1, WITHIN_COM);

[\n]+.*\n	{ int i = 0; putline(yytext, yyleng, OUT_OF_COM);
		  while (yytext[i] == '\n') i++; yyless(i); }
LIBRA[ \t]*	|
DEFINE[ \t]*	|
IN[ \t]*	|
PUBLIC[ \t]*	return JPUBLIC;
HIDE[ \t]*	|
PRIVATE[ \t]*	return JPRIVATE;
"."[ \t]*	|
END[ \t]*	return END;
MODULE[ \t]*	return MODULE;
"=="[ \t]*	return JEQUAL;

false		{ yylval.num = 0; return BOOLEAN_; }
true		{ yylval.num = 1; return BOOLEAN_; }
maxint		{ yylval.num = MAXINT_; return INTEGER_; }

{character}	{ yylval.num = ChrVal(yytext + 1); return CHAR_; }
{integer}	|
{octal}		|
{hexal}		{ yylval.num = strtol(yytext, 0, 0); return INTEGER_; }
{float}		{ yylval.dbl = atof(yytext); return FLOAT_; }
{string}	{ yylval.str = StrVal(yytext + 1); return STRING_; }
{symbol}	{ yylval.str = GC_strdup(yytext); return USR_; }
{comment}	{ if (comment) SkipComment(); else BEGIN COMMENT; }
{linecom}	{ /* default to ECHO */ }
^\$.*		system(yytext + 1);
^\%INCLUDE.*	include(env, DelSpace(yytext + 8), 1);
^\%PUT.*	fprintf(stderr, "%s\n", yytext + 4);
^\%LISTING.*	moy_echo = atoi(yytext + 8);
[ \t\n]+	;
[;[\]{}]	|
.		return yytext[0];
