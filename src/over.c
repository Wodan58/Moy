/*
    module  : over.c
    version : 1.6
    date    : 09/15/23
*/
#ifndef OVER_C
#define OVER_C

/**
OK 3210  over  :  A	X Y  ->  X Y X
[EXT] Pushes an extra copy of the second item X on top of the stack.
*/
void over_(pEnv env)
{
    Node node;

    PARM(2, ANYTYPE);
    node = lst_at(env->stck, lst_size(env->stck) - 2);
    lst_push(env->stck, node);
}
#endif
