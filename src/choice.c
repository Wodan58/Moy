/*
    module  : choice.c
    version : 1.6
    date    : 06/25/18
*/
#include "runtime.h"

/**
choice  :  B T F  ->  X
If B is true, then X = T else X = F.
*/
PRIVATE void do_choice(void)
{
#ifndef NCHECK
    unsigned op, op1;

    if (optimizing) {
	del_history(1);
	op = pop_history(&op1);
	chg_history2(op, op1);
    }
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
