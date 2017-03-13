/*
    module  : frexp.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

/*
frexp  :  F  ->  G I
G is the mantissa and I is the exponent of F.
Unless F = 0, 0.5 <= abs(G) < 1.0.
*/
PRIVATE void do_frexp(void)
{
    int exp;

#ifndef NCHECK
    if (optimizing && NUMERIC_1)
	;
    else
	COMPILE;
    ONEPARAM("frexp");
    FLOAT("frexp");
#endif
    if (OUTSIDE)
	stk->u.dbl = frexp(FLOATVAL, &exp);
    else
	UNARY(FLOAT_NEWNODE, frexp(FLOATVAL, &exp));
    PUSH(INTEGER_, exp);
}
