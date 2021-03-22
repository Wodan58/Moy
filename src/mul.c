/*
    module  : mul.c
    version : 1.11
    date    : 03/15/21
*/
#ifndef MUL_C
#define MUL_C

/**
*  :  I J  ->  K
Integer K is the product of integers I and J.  Also supports float.
*/
PRIVATE void do_mul(pEnv env)
{
#ifndef OLD_RUNTIME
    if (compiling && NUMERIC_1 && NUMERIC_2)
	;
    else
	COMPILE;
#endif
    TWOPARAMS("*");
    FLOAT2("*");
    if (env->stk->next->op == FLOAT_)
	env->stk->next->u.dbl *= FLOATVAL;
    else if (env->stk->op == FLOAT_) {
	env->stk->next->u.dbl = env->stk->next->u.num * env->stk->u.dbl;
	env->stk->next->op = FLOAT_;
    } else
	env->stk->next->u.num *= env->stk->u.num;
    POP(env->stk);
}
#endif
