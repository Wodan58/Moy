%{
/*
    module  : lexer.l
    version : 1.2
    date    : 05/06/16
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <gc.h>
#include "globals1.h"

#ifdef YYLMAX
#undef YYLMAX
#define YYLMAX	2000
#endif

int yylook(void), yywrap(void), yyback(int *, int);

int yyerror(char *str)
{
    extern int yylineno;

    fprintf(stderr, "%d: %s\n", yylineno, str);
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
restchar	({firstchar}{nextchar}*|[-]([-=A-Z_a-z]{nextchar}*)?)
symbol		{restchar}(\.{restchar})*
escape		\\(["'\\btnvfr]|[01][0-9][0-9]|2[0-5][0-5])
character	'([^\\]|{escape})
string		\"([^"\\\n]|{escape})*\"
integer		(0|-?[1-9][0-9]*)
float		{integer}\.[0-9]+([Ee][-+]?[1-9][0-9]*)?
octal		0[1-7][0-7]*
hexal		0[Xx][0-9A-Fa-f]+
linecom		#.*
comment		"(*"")"*([^*)]|[^*]")"|"*"[^)])*"*"*"*)"

%%

"true"		{ yylval.num = 1; return Boolean; }
"false"		{ yylval.num = 0; return Boolean; }
"maxint"	{ yylval.num = MAXINT; return Int; }
{character}	{ yylval.num = ChrVal(yytext + 1); return Char; }
{integer}	|
{octal}		|
{hexal}		{ yylval.num = strtol(yytext, 0, 0); return Int; }
{float}		{ yylval.dbl = atof(yytext); return Float; }
{string}	{ yylval.str = StrVal(yytext + 1); return String; }
{linecom}	|
{comment}	|
[ \t\n\r]+	;
^\$.*		system(yytext + 1);
^\%INCLUDE.*	include(DelSpace(yytext + 8));
^\%PUT.*	fprintf(stderr, "%s\n", yytext + 4);
\.		|
{symbol}	return Keyword(yytext);
.		return yytext[0];
