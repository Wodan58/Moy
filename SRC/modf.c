/*
    module  : modf.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
modf  :  F  ->  G H
G is the fractional part and H is the integer part
(but expressed as a float) of F.
*/
/* modf.c */
PRIVATE void modf_(void)
{
    double exp;

    ONEPARAM("modf");
    FLOAT("modf");
    if (OUTSIDE)
	stk->u.dbl = modf(FLOATVAL, &exp);
    else
	UNARY(FLOAT_NEWNODE, modf(FLOATVAL, &exp));
    FLOAT_PUSH(exp);
}
