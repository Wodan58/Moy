/*
    module  : i.c
    version : 1.4
    date    : 04/15/17
*/
#include "runtime.h"

#ifndef NCHECK
int put_i(void)
{
    Node *prog;

    del_history(1);
    if (!LIST_1)
	return 0;
    prog = stk->u.lis;
    POP(stk);
    printstack(outfp);
    evaluate1(prog);
    return 1;
}
#endif

/*
i  :  [P]  ->  ...
Executes P. So, [P] i  ==  P.
*/
PRIVATE void do_i(void)
{
    Node *prog;

#ifndef NCHECK
    if (optimizing && put_i())
	return;
    COMPILE;
    ONEPARAM("i");
    ONEQUOTE("i");
#endif
    prog = stk->u.lis;
    POP(stk);
    exeterm(prog);
}
