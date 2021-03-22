/*
    module  : frexp.c
    version : 1.10
    date    : 03/15/21
*/
#ifndef FREXP_C
#define FREXP_C

/**
frexp  :  F  ->  G I
G is the mantissa and I is the exponent of F.
Unless F = 0, 0.5 <= abs(G) < 1.0.
*/
PRIVATE void do_frexp(pEnv env)
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
    env->stk->u.dbl = frexp(FLOATVAL, &exp);
    PUSH_NUM(INTEGER_, exp);
}
#endif
