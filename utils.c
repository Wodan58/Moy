/*
    module  : utils.c
    version : 1.14
    date    : 06/28/18
*/
#include "runtime.h"

void readfactor(int sym)
{
    Node temp;
    ulong_t set = 0;

    switch (sym) {
    case '{':
	while ((sym = yylex()) != '}')
	    if (sym == CHAR_ || sym == INTEGER_)
		set |= 1 << yylval.num;
	    else
		execerror("numeric", "set");
	temp.op = SET_;
	temp.u.set = set;
	DUPLICATE(&temp);
	break;
    case '[':
	readterm(yylex());
	break;
    case USR_:
	temp.op = sym;
	temp.u.num = lookup(yylval.str);
	DUPLICATE(&temp);
	break;
    case Symbol:
	temp.u.num = temp.op = yylval.num;
	DUPLICATE(&temp);
	break;
    default:
	temp.op = sym;
	temp.u = yylval;
	DUPLICATE(&temp);
	break;
    }
}

void readterm(int sym)
{
    Node **cur;

    stk = LIST_NEWNODE(0, stk);
    if (sym == ']')
	return;
    cur = &stk->u.lis;
    do {
	readfactor(sym);
	*cur = stk;
	 cur = &stk->next;
	 stk = *cur;
	*cur = 0;
    } while ((sym = yylex()) != ']');
}
