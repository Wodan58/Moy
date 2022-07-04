/*
    module  : ldexp.c
    version : 1.11
    date    : 06/20/22
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

    TWOPARAMS("ldexp");
    INTEGER("ldexp");
    exp = env->stk->u.num;
    POP(env->stk);
    FLOAT("ldexp");
    UNARY(FLOAT_NEWNODE, ldexp(FLOATVAL, exp));
}
#endif
