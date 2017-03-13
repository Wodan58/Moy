/*
    module  : trunc.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

/*
trunc  :  F  ->  I
I is an integer equal to the float F truncated toward zero.
*/
PRIVATE void do_trunc(void)
{
#ifndef NCHECK
    if (optimizing && NUMERIC_1)
	;
    else
	COMPILE;
    ONEPARAM("trunc");
    FLOAT("trunc");
#endif
    if (OUTSIDE) {
	stk->u.num = FLOATVAL;
	stk->op = INTEGER_;
    } else
	UNARY(INTEGER_NEWNODE, (long_t) FLOATVAL);
}
