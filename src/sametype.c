/*
    module  : sametype.c
    version : 1.4
    date    : 04/09/17
*/
#include "runtime.h"

/*
sametype  :  X Y  ->  B
Tests whether X and Y have the same type.
*/
PRIVATE void do_sametype(void)
{
#ifndef NCHECK
    if (optimizing) {
	del_history(1);
	chg_history(BOOLEAN_);
    }
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
