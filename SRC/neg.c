/*
    module  : neg.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

/*
neg  :  I  ->  J
Integer J is the negative of integer I.  Also supports float.
*/
PRIVATE void do_neg(void)
{
#ifndef NCHECK
    if (optimizing && NUMERIC_1)
	;
    else
	COMPILE;
    ONEPARAM("neg");
    FLOAT("neg");
#endif
    if (OUTSIDE) {
	if (stk->op == FLOAT_)
	    stk->u.dbl = -stk->u.dbl;
	else
	    stk->u.num = -stk->u.num;
    } else if (stk->op == FLOAT_)
	UNARY(FLOAT_NEWNODE, -stk->u.dbl);
    else if (stk->u.num)
	UNARY(INTEGER_NEWNODE, -stk->u.num);
}
