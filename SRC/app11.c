/*
    module  : app11.c
    version : 1.3
    date    : 09/19/16
*/
#include "interp.h"

/*
app11  :  X Y [P]  ->  R
Executes P, pushes result R on stack.
*/
PRIVATE void app11_(void)
{
    THREEPARAMS("app11");
    ONEQUOTE("app11");
    app1_();
    if (OUTSIDE) {
	stk[1].op = stk->op;
	stk[1].u = stk->u;
	++stk;
    } else
	stk->next = stk->next->next;
}
