/*
    module  : mul.c
    version : 1.12
    date    : 06/20/22
*/
#ifndef MUL_C
#define MUL_C

/**
*  :  I J  ->  K
Integer K is the product of integers I and J.  Also supports float.
*/
PRIVATE void do_mul(pEnv env)
{
    TWOPARAMS("*");
    FLOAT2("*");
    if (env->stk->next->op == FLOAT_)
	BINARY(FLOAT_NEWNODE, env->stk->next->u.dbl * FLOATVAL);
    else if (env->stk->op == FLOAT_)
	BINARY(FLOAT_NEWNODE, env->stk->next->u.num * env->stk->u.dbl);
    else
	BINARY(INTEGER_NEWNODE, env->stk->next->u.num * env->stk->u.num);
}
#endif
