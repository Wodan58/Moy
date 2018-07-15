/*
    module  : frexp.c
    version : 1.8
    date    : 07/15/18
*/
#ifndef FREXP_X
#define FREXP_C

#ifdef NEW_RUNTIME
void do_frexp(void)
{
    int exp;
    float dbl;

    TRACE;
    memcpy(&dbl, &stk[-1], sizeof(float));
    stk[-1] = frexp(dbl, &exp);
    do_push(exp);
}
#else
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
    if (OUTSIDE)
	stk->u.dbl = frexp(FLOATVAL, &exp);
    else
	UNARY(FLOAT_NEWNODE, frexp(FLOATVAL, &exp));
    PUSH(INTEGER_, exp);
}
#endif
#endif
