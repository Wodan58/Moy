/*
    module  : modf.c
    version : 1.6
    date    : 07/02/18
*/

/**
modf  :  F  ->  G H
G is the fractional part and H is the integer part
(but expressed as a float) of F.
*/
PRIVATE void do_modf(void)
{
    double exp;

#ifndef NCHECK
    if (compiling && NUMERIC_1)
	;
    else
	COMPILE;
#endif
    ONEPARAM("modf");
    FLOAT("modf");
    if (OUTSIDE)
	stk->u.dbl = modf(FLOATVAL, &exp);
    else
	UNARY(FLOAT_NEWNODE, modf(FLOATVAL, &exp));
    DBL_PUSH(exp);
}
