/*
    module  : app1.c
    version : 1.5
    date    : 06/25/18
*/
#include "runtime.h"

#ifndef NCHECK
int put_app1(void)
{
    Node *prog;

    del_history(1);
    if (!LIST_1)
	return 0;
    prog = stk->u.lis;
    POP(stk);
    printstack(outfp);
    evaluate(prog);
    return 1;
}
#endif

/**
app1  :  X [P]  ->  R
Executes P, pushes result R on stack with X.
*/
PRIVATE void do_app1(void)
{
    Node *prog;

#ifndef NCHECK
    if (optimizing && put_app1())
	return;
    COMPILE;
    TWOPARAMS("app1");
    ONEQUOTE("app1");
#endif
    prog = stk->u.lis;
    POP(stk);
    exeterm(prog);
}
