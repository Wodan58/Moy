/*
    module  : unstack.c
    version : 1.14
    date    : 06/20/22
*/
#ifndef UNSTACK_C
#define UNSTACK_C

/**
unstack  :  [X Y ..]  ->  ..Y X
The list [X Y ..] becomes the new stack.
*/
PRIVATE void do_unstack(pEnv env)
{
    ONEPARAM("unstack");
    LIST("unstack");
    env->stk = env->stk->u.lis;
}
#endif
