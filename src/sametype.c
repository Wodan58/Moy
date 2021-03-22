/*
    module  : sametype.c
    version : 1.11
    date    : 03/15/21
*/
#ifndef SAMETYPE_C
#define SAMETYPE_C

/**
sametype  :  X Y  ->  B
Tests whether X and Y have the same type.
*/
PRIVATE void do_sametype(pEnv env)
{
#ifndef OLD_RUNTIME
    if (compiling && VALID_1 && VALID_2)
	;
    else
	COMPILE;
#endif
    TWOPARAMS("sametype");
    env->stk->next->u.num = env->stk->op == env->stk->next->op;
    env->stk->next->op = BOOLEAN_;
    POP(env->stk);
}
#endif
