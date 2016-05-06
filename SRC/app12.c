/*
    module  : app12.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
app12  :  X Y1 Y2 [P]  ->  R1 R2
Executes P twice, with Y1 and Y2, returns R1 and R2.
*/
PRIVATE void app12_(void)
{
    THREEPARAMS("app12");
    unary2_();
    if (inside_condition || inside_critical)
	stk->next->next = stk->next->next->next;
    else {
	stk[2].op = stk[1].op;
	stk[2].u = stk[1].u;
	stk[1].op = stk->op;
	stk[1].u = stk->u;
	++stk;
    }
}
