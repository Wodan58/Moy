/*
    module  : utils.c
    version : 1.2
    date    : 03/15/21
*/
#include "runtime.h"

void readfactor(pEnv env, int sym)
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
	readterm(env, yylex());
	break;
    case SYMBOL_:
	if (interpreter) {
	    temp.op = USR_;
	    temp.u.num = lookup(env, yylval.str);
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

void readterm(pEnv env, int sym)
{
    Node **cur;

    env->stk = LIST_NEWNODE(0, env->stk);
    if (sym == ']')
	return;
    cur = &env->stk->u.lis;
    do {
	readfactor(env, sym);
	*cur = env->stk;
	 cur = &env->stk->next;
	 env->stk = *cur;
	*cur = 0;
    } while ((sym = yylex()) != ']');
}
