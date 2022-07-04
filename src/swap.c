/*
    module  : swap.c
    version : 1.12
    date    : 06/20/22
*/
#ifndef SWAP_C
#define SWAP_C

/**
swap  :  X Y  ->  Y X
Interchanges X and Y on top of the stack.
*/
PRIVATE void do_swap(pEnv env)
{
    Node *first, *second;

    TWOPARAMS("swap");
    first = env->stk;
    POP(env->stk);
    second = env->stk;
    GUNARY(first->op, first->u);
    DUPLICATE(second);
}
#endif
