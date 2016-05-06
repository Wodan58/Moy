/*
    module  : trunc.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
trunc  :  F  ->  I
I is an integer equal to the float F truncated toward zero.
*/
/* trunc.c */
PRIVATE void trunc_(void)
{
    ONEPARAM("trunc");
    FLOAT("trunc");
    if (OUTSIDE) {
	stk->u.num = FLOATVAL;
	stk->op = INTEGER_;
    } else
	UNARY(INTEGER_NEWNODE, (long_t) FLOATVAL);
}
