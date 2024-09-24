/*
    module  : swap.c
    version : 1.8
    date    : 09/17/24
*/
#ifndef SWAP_C
#define SWAP_C

/**
Q0  OK  1220  swap  :  DDAA  X Y  ->  Y X
Interchanges X and Y on top of the stack.
*/
void swap_(pEnv env)
{
    Node first, second;

    PARM(2, ANYTYPE);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    vec_push(env->stck, second);
    vec_push(env->stck, first);
}
#endif
