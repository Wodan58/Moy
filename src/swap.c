/*
    module  : swap.c
    version : 1.10
    date    : 03/28/20
*/
#ifndef SWAP_C
#define SWAP_C

/**
swap  :  X Y  ->  Y X
Interchanges X and Y on top of the stack.
*/
PRIVATE void do_swap(void)
{
    Node temp, *node;

#ifndef OLD_RUNTIME
    if (compiling && VALID_1 && VALID_2)
	;
    else
	COMPILE;
#endif
    TWOPARAMS("swap");
    temp = *stk;
    node = stk->next;
    stk->u = node->u;
    stk->op = node->op;
    node->u = temp.u;
    node->op = temp.op;
}
#endif
