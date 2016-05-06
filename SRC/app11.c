/*
    module  : app11.c
    version : 1.2
    date    : 05/06/16
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
    if (inside_condition || inside_critical)
	stk->next = stk->next->next;
    else {
	stk[1].op = stk->op;
	stk[1].u = stk->u;
	++stk;
    }
}
