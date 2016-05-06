/*
    module  : rollup.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
rollup  :  X Y Z  ->  Z X Y
Moves X and Y up, moves Z down.
*/
/* rollup.c */
PRIVATE void rollup_(void)
{
    Node temp, *node, *next;

    THREEPARAMS("rollup");
    temp = *stk;
    node = stk->next;
    next = node->next;
    if (OUTSIDE) {
	stk->u = node->u;
	stk->op = node->op;
	node->u = next->u;
	node->op = next->op;
	next->u = temp.u;
	next->op = temp.op;
	return;
    }
    GTERNARY(temp.op, temp.u.ptr);
    GNULLARY(next->op, next->u.ptr);
    GNULLARY(node->op, node->u.ptr);
}
