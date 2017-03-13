/*
    module  : app11.c
    version : 1.4
    date    : 03/12/17
*/
#include "runtime.h"

/*
app11  :  X Y [P]  ->  R
Executes P, pushes result R on stack.
*/
PRIVATE void do_app11(void)
{
#ifndef NCHECK
    COMPILE;
    THREEPARAMS("app11");
    ONEQUOTE("app11");
#endif
    do_app1();
    if (OUTSIDE) {
	stk[-1].op = stk->op;
	stk[-1].u = stk->u;
	stk--;
    } else
	stk->next = stk->next->next;
}
