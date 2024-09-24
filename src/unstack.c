/*
    module  : unstack.c
    version : 1.9
    date    : 09/17/24
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
    node = vec_pop(env->stck);
    vec_copy_count(env->stck, node.u.lis, vec_size(node.u.lis));
}
#endif
