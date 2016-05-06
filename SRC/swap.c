/*
    module  : swap.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
swap  :  X Y  ->  Y X
Interchanges X and Y on top of the stack.
*/
/* swap.c */
PRIVATE void swap_(void)
{
    Node temp, *node;

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
