/*
    module  : casting.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

/*
casting  :  X Y  ->  Z
Z takes the value from X and the type from Y.
*/
PRIVATE void do_casting(void)
{
#ifndef NCHECK
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
