/*
    module  : unstack.c
    version : 1.4
    date    : 09/11/23
*/
#ifndef UNSTACK_C
#define UNSTACK_C

/**
OK 2000  unstack  :  DU	[X Y ..]  ->  ..Y X
The list [X Y ..] becomes the new stack.
*/
void unstack_(pEnv env)
{
#ifndef COMPILER
    Node node;

    PARM(1, HELP);
    node = lst_pop(env->stck);
    lst_copy(env->stck, node.u.lis);
#endif
}
#endif
