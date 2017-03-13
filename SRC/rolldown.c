/*
    module  : rolldown.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

/*
rolldown  :  X Y Z  ->  Y Z X
Moves Y and Z down, moves X up.
*/
PRIVATE void do_rolldown(void)
{
    Node temp, *node, *next;

#ifndef NCHECK
    if (optimizing && VALID(stk) && VALID(stk->next) && VALID(stk->next->next))
	;
    else
	COMPILE;
    THREEPARAMS("rolldown");
#endif
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
