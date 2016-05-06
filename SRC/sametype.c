/*
    module  : sametype.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
sametype  :  X Y  ->  B
Tests whether X and Y have the same type.
*/
/* sametype.c */
PRIVATE void sametype_(void)
{
    TWOPARAMS("sametype");
    if (OUTSIDE) {
	stk->next->u.num = stk->op == stk->next->op;
	stk->next->op = BOOLEAN_;
	POP(stk);
    } else
	BINARY(BOOLEAN_NEWNODE, stk->op == stk->next->op);
}
