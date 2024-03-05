/*
    module  : unstack.c
    version : 1.8
    date    : 03/05/24
*/
#ifndef UNSTACK_C
#define UNSTACK_C

/**
Q0  OK  2000  unstack  :  DP  [X Y ..]  ->  ..Y X
The list [X Y ..] becomes the new stack.
*/
void unstack_(pEnv env)
{
    Node node;

    PARM(1, HELP);
    env->stck = pvec_pop(env->stck, &node);
    pvec_copy(env->stck, node.u.lis);
}
#endif
