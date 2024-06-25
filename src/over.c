/*
    module  : over.c
    version : 1.12
    date    : 06/22/24
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
    node = pvec_nth(env->stck, pvec_cnt(env->stck) - 2);
    env->stck = pvec_add(env->stck, node);
}
#endif
