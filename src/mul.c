/*
    module  : mul.c
    version : 1.5
    date    : 06/25/18
*/
#include "runtime.h"

/**
*  :  I J  ->  K
Integer K is the product of integers I and J.  Also supports float.
*/
PRIVATE void do_mul(void)
{
#ifndef NCHECK
    if (optimizing)
	del_history(1);
    if (optimizing && NUMERIC_1 && NUMERIC_2)
	;
    else
	COMPILE;
    TWOPARAMS("*");
    FLOAT2("*");
#endif
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
