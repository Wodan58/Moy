/*
    module  : while.c
    version : 1.6
    date    : 10/04/16
*/
#include "interp.h"

/*
while  :  [B] [D]  ->  ...
While executing B yields true executes D.
*/
/* while.c */
PRIVATE void while_(void)
{
    int num;
    Node *prog, *list, *save;
#ifdef ARITY
    int d;
#endif

    TWOPARAMS("while");
    TWOQUOTES("while");
    prog = stk->u.lis;
    POP(stk);
    list = stk->u.lis;
    POP(stk);
#ifdef ARITY
    d = arity(list);
#endif
    for (;;) {
	save = stk;
#ifdef ARITY
	copy_(d);
#else
	CONDITION;
#endif
	exeterm(list);
	num = stk->u.num;
	stk = save;
#ifndef ARITY
	RELEASE;
#endif
	if (!num)
	    break;
	exeterm(prog);
    }
}
