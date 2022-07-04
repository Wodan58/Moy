/*
    module  : rem.c
    version : 1.12
    date    : 06/20/22
*/
#ifndef REM_C
#define REM_C

/**
rem  :  I J  ->  K
Integer K is the remainder of dividing I by J.  Also supports float.
*/
PRIVATE void do_rem(pEnv env)
{
    TWOPARAMS("rem");
    FLOAT2("rem");
    CHECKZERO("rem");
    if (env->stk->next->op == FLOAT_)
	BINARY(FLOAT_NEWNODE, fmod(env->stk->next->u.dbl, FLOATVAL));
    else if (env->stk->op == FLOAT_)
	BINARY(FLOAT_NEWNODE, fmod((double)env->stk->next->u.num,
				   env->stk->u.dbl));
    else
	BINARY(INTEGER_NEWNODE, env->stk->next->u.num % env->stk->u.num);
}
#endif
