/*
    module  : frexp.c
    version : 1.6
    date    : 07/02/18
*/

/**
frexp  :  F  ->  G I
G is the mantissa and I is the exponent of F.
Unless F = 0, 0.5 <= abs(G) < 1.0.
*/
PRIVATE void do_frexp(void)
{
    int exp;

#ifndef NCHECK
    if (compiling && NUMERIC_1)
	;
    else
	COMPILE;
#endif
    ONEPARAM("frexp");
    FLOAT("frexp");
    if (OUTSIDE)
	stk->u.dbl = frexp(FLOATVAL, &exp);
    else
	UNARY(FLOAT_NEWNODE, frexp(FLOATVAL, &exp));
    PUSH(INTEGER_, exp);
}
