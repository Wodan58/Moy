/*
    module  : mul.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
*  :  I J  ->  K
Integer K is the product of integers I and J.  Also supports float.
*/
/* mul.c */
PRIVATE void mul_(void)
{
    TWOPARAMS("*");
    FLOAT2("*");
    if (OUTSIDE) {
	if (stk->next->op == FLOAT_)
	    stk->next->u.dbl *= FLOATVAL;
	else if (stk->op == FLOAT_) {
	    stk->next->u.dbl = stk->next->u.num * stk->u.dbl;
	    stk->next->op = FLOAT_;
	} else
	    stk->next->u.num *= stk->u.num;
	POP(stk);
    } else if (stk->op == FLOAT_ || stk->next->op == FLOAT_)
	BINARY(FLOAT_NEWNODE, (FLOATVAL2) * (FLOATVAL));
    else
	BINARY(INTEGER_NEWNODE, stk->next->u.num * stk->u.num);
}
