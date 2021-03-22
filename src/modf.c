/*
    module  : modf.c
    version : 1.10
    date    : 03/15/21
*/
#ifndef MODF_C
#define MODF_C

/**
modf  :  F  ->  G H
G is the fractional part and H is the integer part
(but expressed as a float) of F.
*/
PRIVATE void do_modf(pEnv env)
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
    env->stk->u.dbl = modf(FLOATVAL, &exp);
    PUSH_DBL(exp);
}
#endif
