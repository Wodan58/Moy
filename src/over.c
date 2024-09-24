/*
    module  : over.c
    version : 1.13
    date    : 09/17/24
*/
#ifndef OVER_C
#define OVER_C

/**
Q0  OK  3180  over  :  A  X Y  ->  X Y X
[EXT] Pushes an extra copy of the second item X on top of the stack.
*/
void over_(pEnv env)
{
    Node node;

    PARM(2, ANYTYPE);
    node = vec_at(env->stck, vec_size(env->stck) - 2);
    vec_push(env->stck, node);
}
#endif
