/*
    module  : frexp.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
frexp  :  F  ->  G I
G is the mantissa and I is the exponent of F.
Unless F = 0, 0.5 <= abs(G) < 1.0.
*/
/* frexp.c */
PRIVATE void frexp_(void)
{
    int exp;

    ONEPARAM("frexp");
    FLOAT("frexp");
    if (OUTSIDE)
	stk->u.dbl = frexp(FLOATVAL, &exp);
    else
	UNARY(FLOAT_NEWNODE, frexp(FLOATVAL, &exp));
    PUSH(INTEGER_, (long_t)exp);
}
