/*
    module  : rolldown.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
rolldown  :  X Y Z  ->  Y Z X
Moves Y and Z down, moves X up.
*/
/* rolldown.c */
PRIVATE void rolldown_(void)
{
    Node temp, *node, *next;

    THREEPARAMS("rolldown");
    node = stk->next;
    next = node->next;
    temp = *next;
    if (OUTSIDE) {
	next->u = node->u;
	next->op = node->op;
	node->u = stk->u;
	node->op = stk->op;
	stk->u = temp.u;
	stk->op = temp.op;
	return;
    }
    temp = *stk;
    GTERNARY(node->op, node->u.ptr);
    GNULLARY(temp.op, temp.u.ptr);
    GNULLARY(next->op, next->u.ptr);
}
