/*
    module  : swap.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef SWAP_C
#define SWAP_C

/**
OK 1220  swap  :  DDAA	X Y  ->  Y X
Interchanges X and Y on top of the stack.
*/
void swap_(pEnv env)
{
    Node first, second;

    PARM(2, ANYTYPE);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    env->stck = pvec_add(env->stck, second);
    env->stck = pvec_add(env->stck, first);
}
#endif
