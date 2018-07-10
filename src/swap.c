/*
    module  : swap.c
    version : 1.8
    date    : 07/10/18
*/
#ifndef SWAP_X
#define SWAP_C

#ifdef RUNTIME
void do_swap(void)
{
    node_t temp;

    TRACE;
    temp = stk[-1];
    stk[-1] = stk[-2];
    stk[-2] = temp;
}
#else
/**
swap  :  X Y  ->  Y X
Interchanges X and Y on top of the stack.
*/
PRIVATE void do_swap(void)
{
    Node temp, *node;

#ifndef NCHECK
    if (compiling && VALID_1 && VALID_2)
	;
    else
	COMPILE;
#endif
    TWOPARAMS("swap");
    temp = *stk;
    node = stk->next;
    if (OUTSIDE) {
	stk->u = node->u;
	stk->op = node->op;
	node->u = temp.u;
	node->op = temp.op;
	return;
    }
    GBINARY(temp.op, temp.u.ptr);
    GNULLARY(node->op, node->u.ptr);
}
#endif
#endif
