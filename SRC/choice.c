/*
    module  : choice.c
    version : 1.4
    date    : 03/12/17
*/
#include "runtime.h"

/*
choice  :  B T F  ->  X
If B is true, then X = T else X = F.
*/
PRIVATE void do_choice(void)
{
#ifndef NCHECK
    if (optimizing && VALID(stk) && VALID(stk->next) && VALID(stk->next->next))
	;
    else
	COMPILE;
    THREEPARAMS("choice");
#endif
    if (OUTSIDE) {
	if (stk->next->next->u.num) {
	    stk->next->next->u = stk->next->u;
	    stk->next->next->op = stk->next->op;
	} else {
	    stk->next->next->u = stk->u;
	    stk->next->next->op = stk->op;
	}
	POP(stk);
	POP(stk);
    } else if (stk->next->next->u.num)
	GTERNARY(stk->next->op, stk->next->u.ptr);
    else
	GTERNARY(stk->op, stk->u.ptr);
}
