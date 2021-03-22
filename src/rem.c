/*
    module  : rem.c
    version : 1.11
    date    : 03/15/21
*/
#ifndef REM_C
#define REM_C

/**
rem  :  I J  ->  K
Integer K is the remainder of dividing I by J.  Also supports float.
*/
PRIVATE void do_rem(pEnv env)
{
#ifndef OLD_RUNTIME
    if (compiling && NUMERIC_1 && NUMERIC_2)
	;
    else
	COMPILE;
#endif
    TWOPARAMS("rem");
    FLOAT2("rem");
#ifndef NCHECK
    if ((env->stk->op == FLOAT_ && !env->stk->u.dbl) ||
	(env->stk->op == INTEGER_ && !env->stk->u.num))
	execerror("non-zero operand", "rem");
#endif
    if (env->stk->next->op == FLOAT_)
	env->stk->next->u.dbl = fmod(env->stk->next->u.dbl, FLOATVAL);
    else if (env->stk->op == FLOAT_) {
	env->stk->next->u.dbl = fmod((double) env->stk->next->u.num, env->stk->u.dbl);
	env->stk->next->op = FLOAT_;
    } else
	env->stk->next->u.num %= env->stk->u.num;
    POP(env->stk);
}
#endif
