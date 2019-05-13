/*
    module  : factor.c
    version : 1.4
    date    : 05/13/19
*/
#include <stdio.h>
#include "joy.h"
#include "prims.h"

YYSTYPE yylval;

void readfactor(int sym)
{
    ulong_t set = 0;

    switch (sym) {
    case '{':
	while ((sym = yylex()) != '}')
	    if (sym == CHAR_ || sym == INTEGER_)
		set |= 1 << yylval.num;
	    else
		execerror("numeric", "set");
	do_push(set);
	break;
    case '[':
	readterm(yylex());
	break;
    case SYMBOL_:
	yylval.proc = nameproc(yylval.str);
	/* continue */
    default:
	do_push(yylval.num);
	break;
    }
}

void readterm(int sym)
{
    code_t **cur;

    do_push(0);
    if (sym == ']')
	return;
    cur = (code_t **)&stk[-1];
    do {
	readfactor(sym);
	*cur = joy_code();
	(*cur)->num = do_pop();
	cur = &(*cur)->next;
    } while ((sym = yylex()) != ']');
}
