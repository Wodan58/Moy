/*
    module  : modf.c
    version : 1.9
    date    : 03/28/20
*/
#ifndef MODF_C
#define MODF_C

/**
modf  :  F  ->  G H
G is the fractional part and H is the integer part
(but expressed as a float) of F.
*/
PRIVATE void do_modf(void)
{
    double exp;

#ifndef OLD_RUNTIME
    if (compiling && NUMERIC_1)
	;
    else
	COMPILE;
#endif
    ONEPARAM("modf");
    FLOAT("modf");
    stk->u.dbl = modf(FLOATVAL, &exp);
    DBL_PUSH(exp);
}
#endif
