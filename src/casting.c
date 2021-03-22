/*
    module  : casting.c
    version : 1.10
    date    : 03/15/21
*/
#ifndef CASTING_C
#define CASTING_C

/**
casting  :  X Y  ->  Z
Z takes the value from X and the type from Y.
*/
PRIVATE void do_casting(pEnv env)
{
#ifndef OLD_RUNTIME
    if (compiling && VALID_1 && VALID_2)
	;
    else
	COMPILE;
#endif
    TWOPARAMS("casting");
    env->stk->next->op = env->stk->op;
    POP(env->stk);
}
#endif
