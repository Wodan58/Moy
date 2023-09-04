/*
    module  : unstack.c
    version : 1.3
    date    : 09/04/23
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
    node = lst_pop(env->stck);
    lst_copy(env->stck, node.u.lis);
}
#endif
