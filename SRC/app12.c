/*
    module  : app12.c
    version : 1.4
    date    : 03/12/17
*/
#include "runtime.h"

/*
app12  :  X Y1 Y2 [P]  ->  R1 R2
Executes P twice, with Y1 and Y2, returns R1 and R2.
*/
PRIVATE void do_app12(void)
{
#ifndef NCHECK
    COMPILE;
    THREEPARAMS("app12");
#endif
    do_unary2();
    if (OUTSIDE) {
	stk[-2].op = stk[-1].op;
	stk[-2].u = stk[-1].u;
	stk[-1].op = stk->op;
	stk[-1].u = stk->u;
	stk--;
    } else
	stk->next->next = stk->next->next->next;
}
