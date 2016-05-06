/*
    module  : casting.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
casting  :  X Y  ->  Z
Z takes the value from X and the type from Y.
*/
/* casting.c */
PRIVATE void casting_(void)
{
    TWOPARAMS("casting");
    if (OUTSIDE) {
	stk->next->op = stk->op;
	POP(stk);
    } else
	GBINARY(stk->op, stk->next->u.ptr);
}
