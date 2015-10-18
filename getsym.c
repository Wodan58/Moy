/*
    module  : getsym.c
    version : 1.1
    date    : 10/18/15
*/
#include <stdio.h>
#include <string.h>
#include "globals.h"

int yylex();

void getsym(void)
{
    int ch;

    switch (ch = yylex()) {
    case Boolean:
	sym = BOOLEAN_;
	num = yylval.num;
	break;

    case Int:
	sym = INTEGER_;
	num = yylval.num;
	break;

    case Char:
	sym = CHAR_;
	num = yylval.num;
	break;

    case String:
	sym = STRING_;
	bucket.str = yylval.str;
	break;

    case Float:
	sym = FLOAT_;
	dbl = yylval.dbl;
	break;

    case JSymbol:
	sym = ATOM;
	strncpy(id, yylval.str, ALEN);
	id[ALEN - 1] = 0;
	break;

    default:
	sym = ch;
	break;
    }
}
