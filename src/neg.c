/*
    module  : neg.c
    version : 1.9
    date    : 03/15/21
*/
#ifndef NEG_C
#define NEG_C

/**
neg  :  I  ->  J
Integer J is the negative of integer I.  Also supports float.
*/
PRIVATE void do_neg(pEnv env)
{
#ifndef OLD_RUNTIME
    if (compiling && NUMERIC_1)
	;
    else
	COMPILE;
#endif
    ONEPARAM("neg");
    FLOAT("neg");
    if (env->stk->op == FLOAT_)
	env->stk->u.dbl = -env->stk->u.dbl;
    else
	env->stk->u.num = -env->stk->u.num;
}
#endif
