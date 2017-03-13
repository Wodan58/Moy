/*
    module  : sign.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

/*
sign  :  N1  ->  N2
Integer N2 is the sign (-1 or 0 or +1) of integer N1,
or float N2 is the sign (-1.0 or 0.0 or 1.0) of float N1.
*/
PRIVATE double fsgn(double f)
{
    if (f < 0)
	return -1.0;
    else if (f > 0)
	return 1.0;
    else
	return 0.0;
}

PRIVATE void do_sign(void)
{
#ifndef NCHECK
    if (optimizing && NUMERIC_1)
	;
    else
	COMPILE;
    ONEPARAM("sign");
    FLOAT("sign");
#endif
    if (OUTSIDE) {
	if (stk->op == FLOAT_)
	    stk->u.dbl = fsgn(stk->u.dbl);
	else if (stk->u.num < 0 || stk->u.num > 1)
	    stk->u.num = stk->u.num > 0 ? 1 : -1;
    } else if (stk->op == FLOAT_)
	UNARY(FLOAT_NEWNODE, fsgn(FLOATVAL));
    else if (stk->u.num < 0 || stk->u.num > 1)
	UNARY(INTEGER_NEWNODE, stk->u.num > 0 ? 1 : -1);
}
