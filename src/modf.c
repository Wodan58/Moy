/*
    module  : modf.c
    version : 1.7
    date    : 07/10/18
*/
#ifndef MODF_X
#define MODF_C

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
#endif
