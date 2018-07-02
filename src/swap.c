/*
    module  : swap.c
    version : 1.6
    date    : 07/02/18
*/

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
