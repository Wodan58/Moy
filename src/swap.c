/*
    module  : swap.c
    version : 1.11
    date    : 03/15/21
*/
#ifndef SWAP_C
#define SWAP_C

/**
swap  :  X Y  ->  Y X
Interchanges X and Y on top of the stack.
*/
PRIVATE void do_swap(pEnv env)
{
    Node temp, *node;

#ifndef OLD_RUNTIME
    if (compiling && VALID_1 && VALID_2)
	;
    else
	COMPILE;
#endif
    TWOPARAMS("swap");
    temp = *env->stk;
    node = env->stk->next;
    env->stk->u = node->u;
    env->stk->op = node->op;
    node->u = temp.u;
    node->op = temp.op;
}
#endif
