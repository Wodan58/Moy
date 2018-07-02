%{
/*
    module  : lexer.l
    version : 1.17
    date    : 07/02/18
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "joy.h"
#include "symbol.h"
#include "decl.h"

static int moy_echo;
static char buf[MAXLINE];

#ifdef FLEX_SCANNER
int include_stack_ptr;
YY_BUFFER_STATE include_stack[MAX_INCLUDE];

static int input(void);
#endif

int getechoflag(void)
{
    return moy_echo;
}

void setechoflag(int flag)
{
    moy_echo = flag;
}

static void putline(void)
{
    if (moy_echo > 2)
	printf("%4d", yylineno);
    if (moy_echo > 1)
	printf("\t");
    if (moy_echo)
	printf("%s", buf + 1);
}

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
    if (include_stack_ptr >= MAX_INCLUDE)
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

int yyerror(char *str)
{
    fprintf(stderr, "%s in line %d near %.*s\n", str, yylineno, yyleng, yytext);
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

\n.*\n		{ int i; strncpy(buf, yytext, MAXLINE); buf[MAXLINE - 1] = 0;
		  for (i = yyleng - 1; i; i--) unput(yytext[i]); putline(); }
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
{comment}	SkipComment();
[ \t\n]+	|
{linecom}	;
^\$.*		system(yytext + 1);
^\%INCLUDE.*	include(DelSpace(yytext + 8));
^\%PUT.*	fprintf(stderr, "%s\n", yytext + 4);
^\%LISTING.*	moy_echo = atoi(yytext + 8);
[;[\]{}]	return yytext[0];
[^ \t\n]+	{ yylval.str = strdup(yytext); return SYMBOL_; }
