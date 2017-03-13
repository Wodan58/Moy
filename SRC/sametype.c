/*
    module  : sametype.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

/*
sametype  :  X Y  ->  B
Tests whether X and Y have the same type.
*/
PRIVATE void do_sametype(void)
{
#ifndef NCHECK
    if (optimizing && VALID(stk) && VALID(stk->next))
	;
    else
	COMPILE;
    TWOPARAMS("sametype");
#endif
    if (OUTSIDE) {
	stk->next->u.num = stk->op == stk->next->op;
	stk->next->op = BOOLEAN_;
	POP(stk);
    } else
	BINARY(BOOLEAN_NEWNODE, stk->op == stk->next->op);
}
