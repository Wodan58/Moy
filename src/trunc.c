/*
    module  : trunc.c
    version : 1.10
    date    : 03/15/21
*/
#ifndef TRUNC_C
#define TRUNC_C

/**
trunc  :  F  ->  I
I is an integer equal to the float F truncated toward zero.
*/
PRIVATE void do_trunc(pEnv env)
{
#ifndef OLD_RUNTIME
    if (compiling && NUMERIC_1)
	;
    else
	COMPILE;
#endif
    ONEPARAM("trunc");
    FLOAT("trunc");
    env->stk->u.num = FLOATVAL;
    env->stk->op = INTEGER_;
}
#endif
