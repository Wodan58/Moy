%{
/*
    module  : lexer.l
    version : 1.21
    date    : 08/17/20
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "joy.h"
#include "symbol.h"
#include "decl.h"

#define OUT_OF_COM	0
#define WITHIN_COM	1
#define LEAVE_COMM	2

char line[INPLINEMAX + 1];
static int moy_echo, comment;

#ifdef FLEX_SCANNER
int include_stack_ptr;
YY_BUFFER_STATE include_stack[INPSTACKMAX];

static int input(void);
#endif

static void SkipComment(void)
{
    int ch;

    ch = input();
    do {
	while (ch != '*' && ch != EOF)
	    ch = input();
#if 0
	if (ch == EOF)
	    execerror("no EOF", "SkipComment");
#endif
    } while ((ch = input()) != ')');
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
    int i, linenum, start, finish;

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
	    return; /* add start of comment */
	}
    } else if (!first) {
	first = 1;
	if (strstr(line, "(*"))
	    goto skip;
	addline('('); /* add start of comment */
	addline('*');
    }
skip:
    for (i = 0; i < leng; i++)
	addline(str[i]);
    if (!moy_echo)
	return;
    if (moy_echo > 2) {
	if (status == LEAVE_COMM)
	    linenum = yylineno;	/* yylineno should not be corrected */
	else
	    linenum = yylineno - 1;
	fprintf(stderr, "%4d", linenum);
    }
    if (moy_echo > 1)
	fprintf(stderr, "\t");
    fprintf(stderr, "%s\n", line); /* include newline */
}

void new_buffer(void)
{
#ifdef FLEX_SCANNER
    if (include_stack_ptr >= INPSTACKMAX)
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

%option		yylineno
%x		COMMENT

firstchar	[!$%&*+,./:<=>?@A-Z\\^_`a-z|~]
secondchar	[*+/<>]
nextchar	[-0-9=A-Z_a-z]
restchar	({firstchar}{secondchar}?{nextchar}*|[-]([-*+/<=>A-Z_a-z]{nextchar}*)?)
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

<COMMENT>"*)"	{ putline("*)", 2, LEAVE_COMM); BEGIN INITIAL; }
<COMMENT>.	addline(yytext[0]);
<COMMENT>\n	putline("\n", 1, WITHIN_COM);

[\n]+.*\n	{ int i; putline(yytext, yyleng, OUT_OF_COM); for (i = 0;
		  yytext[i] == '\n'; i++); yyless(i); }
LIBRA		|
DEFINE		|
IN		|
PUBLIC		return JPUBLIC;
HIDE		|
PRIVATE		return JPRIVATE;
"."		|
END		return END;
MODULE		return MODULE;
"=="		return JEQUAL;

false		{ yylval.num = 0; return BOOLEAN_; }
true		{ yylval.num = 1; return BOOLEAN_; }
maxint		{ yylval.num = MAXINT_; return INTEGER_; }

{character}	{ yylval.num = ChrVal(yytext + 1); return CHAR_; }
{integer}	|
{octal}		|
{hexal}		{ yylval.num = strtol(yytext, 0, 0); return INTEGER_; }
{float}		{ yylval.dbl = atof(yytext); return FLOAT_; }
{string}	{ yylval.str = StrVal(yytext + 1); return STRING_; }
{comment}	{ if (comment) SkipComment(); else BEGIN COMMENT; }
[ \t\n]+	|
{linecom}	;
^\$.*		system(yytext + 1);
^\%INCLUDE.*	include(DelSpace(yytext + 8));
^\%PUT.*	fprintf(stderr, "%s\n", yytext + 4);
^\%LISTING.*	moy_echo = atoi(yytext + 8);
{symbol}	{ yylval.str = ck_strdup(yytext); return SYMBOL_; }
[;[\]{}]	|
.		return yytext[0];
