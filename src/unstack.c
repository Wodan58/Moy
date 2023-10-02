/*
    module  : unstack.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef UNSTACK_C
#define UNSTACK_C

/**
OK 2000  unstack  :  DU	[X Y ..]  ->  ..Y X
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
