/*
    module  : swap.c
    version : 1.5
    date    : 09/15/23
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
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
    lst_push(env->stck, second);
    lst_push(env->stck, first);
}
#endif
