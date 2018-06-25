/*
    module  : casting.c
    version : 1.5
    date    : 06/25/18
*/
#include "runtime.h"

/**
casting  :  X Y  ->  Z
Z takes the value from X and the type from Y.
*/
PRIVATE void do_casting(void)
{
#ifndef NCHECK
    unsigned op, op1;

    if (optimizing) {
	op = pop_history(&op1);
	chg_history2(op, op1);
    }
    if (optimizing && VALID(stk) && VALID(stk->next))
	;
    else
	COMPILE;
    TWOPARAMS("casting");
#endif
    if (OUTSIDE) {
	stk->next->op = stk->op;
	POP(stk);
    } else
	GBINARY(stk->op, stk->next->u.ptr);
}
