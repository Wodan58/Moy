/*
    module  : casting.c
    version : 1.11
    date    : 06/20/22
*/
#ifndef CASTING_C
#define CASTING_C

/**
casting  :  X Y  ->  Z
Z takes the value from X and the type from Y.
*/
PRIVATE void do_casting(pEnv env)
{
    TWOPARAMS("casting");
    GBINARY(env->stk->op, env->stk->next->u);
}
#endif
