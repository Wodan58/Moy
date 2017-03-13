/*
    module  : modf.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

/*
modf  :  F  ->  G H
G is the fractional part and H is the integer part
(but expressed as a float) of F.
*/
PRIVATE void do_modf(void)
{
    double exp;

#ifndef NCHECK
    if (optimizing && NUMERIC_1)
	;
    else
	COMPILE;
    ONEPARAM("modf");
    FLOAT("modf");
#endif
    if (OUTSIDE)
	stk->u.dbl = modf(FLOATVAL, &exp);
    else
	UNARY(FLOAT_NEWNODE, modf(FLOATVAL, &exp));
    DBL_PUSH(exp);
}
