/*
    module  : divide.c
    version : 1.11
    date    : 03/15/21
*/
#ifndef DIVIDE_C
#define DIVIDE_C

/**
/  :  I J  ->  K
Integer K is the (rounded) ratio of integers I and J.  Also supports float.
*/
PRIVATE void do_divide(pEnv env)
{
#ifndef OLD_RUNTIME
    if (compiling && NUMERIC_1 && NUMERIC_2)
	;
    else
	COMPILE;
#endif
    TWOPARAMS("/");
    FLOAT2("/");
#ifndef NCHECK
    if ((env->stk->op == FLOAT_ && !env->stk->u.dbl) ||
	(env->stk->op == INTEGER_ && !env->stk->u.num))
	execerror("non-zero divisor", "/");
#endif
    if (env->stk->next->op == FLOAT_)
	env->stk->next->u.dbl /= FLOATVAL;
    else if (env->stk->op == FLOAT_) {
	env->stk->next->u.dbl = env->stk->next->u.num / env->stk->u.dbl;
	env->stk->next->op = FLOAT_;
    } else
	env->stk->next->u.num /= env->stk->u.num;
    POP(env->stk);
}
#endif
