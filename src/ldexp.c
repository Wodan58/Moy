/*
    module  : ldexp.c
    version : 1.10
    date    : 03/15/21
*/
#ifndef LDEXP_C
#define LDEXP_C

/**
ldexp  :  F I  ->  G
G is F times 2 to the Ith power.
*/
PRIVATE void do_ldexp(pEnv env)
{
    int exp;

#ifndef OLD_RUNTIME
    if (compiling && INTEGER_1 && NUMERIC_2)
	;
    else
	COMPILE;
#endif
    TWOPARAMS("ldexp");
    INTEGER("ldexp");
    exp = env->stk->u.num;
    POP(env->stk);
    FLOAT("ldexp");
    env->stk->u.dbl = ldexp(FLOATVAL, exp);
}
#endif
