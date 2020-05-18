/*
    module  : utils.c
    version : 1.1
    date    : 05/13/20
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
		set |= (ulong_t)1 << yylval.num;
	    else
		execerror("numeric", "set");
	temp.op = SET_;
	temp.u.set = set;
	DUPLICATE(&temp);
	break;
    case '[':
	readterm(yylex());
	break;
    case SYMBOL_:
	if (interpreter) {
	    temp.op = USR_;
	    temp.u.num = lookup(yylval.str);
	} else if ((temp.u.proc = nameproc(yylval.str)) != 0)
	    temp.op = ANON_FUNCT_;
	else {
	    temp.op = SYMBOL_;
	    temp.u.str = yylval.str;
	}
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
