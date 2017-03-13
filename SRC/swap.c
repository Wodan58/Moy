/*
    module  : swap.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

/*
swap  :  X Y  ->  Y X
Interchanges X and Y on top of the stack.
*/
PRIVATE void do_swap(void)
{
    Node temp, *node;

#ifndef NCHECK
    if (optimizing && VALID(stk) && VALID(stk->next))
	;
    else
	COMPILE;
    TWOPARAMS("swap");
#endif
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
