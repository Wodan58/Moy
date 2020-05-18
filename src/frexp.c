/*
    module  : frexp.c
    version : 1.9
    date    : 03/28/20
*/
#ifndef FREXP_C
#define FREXP_C

/**
frexp  :  F  ->  G I
G is the mantissa and I is the exponent of F.
Unless F = 0, 0.5 <= abs(G) < 1.0.
*/
PRIVATE void do_frexp(void)
{
    int exp;

#ifndef OLD_RUNTIME
    if (compiling && NUMERIC_1)
	;
    else
	COMPILE;
#endif
    ONEPARAM("frexp");
    FLOAT("frexp");
    stk->u.dbl = frexp(FLOATVAL, &exp);
    PUSH(INTEGER_, exp);
}
#endif
