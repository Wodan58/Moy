/*
    module  : over.c
    version : 1.3
    date    : 08/26/23
*/
#ifndef OVER_C
#define OVER_C

/**
OK 1213  over  :  A	X Y  ->  X Y X
Pushes an extra copy of the second item X on top of the stack.
*/
void over_(pEnv env)
{
    Node node;

    PARM(2, ANYTYPE);
    node = lst_at(env->stck, lst_size(env->stck) - 2);
    lst_push(env->stck, node);
}
#endif
