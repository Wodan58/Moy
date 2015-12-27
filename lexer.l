%{
/*
    module  : lexer.l
    version : 1.2
    date    : 12/27/15
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <gc.h>
#define malloc  GC_malloc
#define realloc GC_realloc
#define free(X) ((X)?(X++):0)
#include "globals1.h"

#ifdef YYLMAX
#undef YYLMAX
#define YYLMAX	2000
#endif

int yylook(), yywrap(), yyback();

int yyerror(char *str)
{
    fprintf(stderr, "ERROR: %s\n", str);
    return 0;
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
escape		\\(["'\\btnvfr]|[0-1][0-9][0-9]|2[0-5][0-5])
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
{hexal}		{ yylval.num = strtoll(yytext, 0, 0); return Int; }
{float}		{ yylval.dbl = atof(yytext); return Float; }
{string}	{ yylval.str = StrVal(yytext + 1); return String; }
{linecom}	|
{comment}	|
[ \t\n\r]+	;
^\$.*		system(yytext + 1);
\.		|
{symbol}	return Keyword(yytext);
.		return yytext[0];
