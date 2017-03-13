/*
    module  : rotate.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

/*
rotate  :  X Y Z  ->  Z Y X
Interchanges X and Z.
*/
PRIVATE void do_rotate(void)
{
    Node temp, *node, *next;

#ifndef NCHECK
    if (optimizing && VALID(stk) && VALID(stk->next) && VALID(stk->next->next))
	;
    else
	COMPILE;
    THREEPARAMS("rotate");
#endif
    temp = *stk;
    node = stk->next;
    next = node->next;
    if (OUTSIDE) {
	stk->u = next->u;
	stk->op = next->op;
	next->u = temp.u;
	next->op = temp.op;
	return;
    }
    GTERNARY(temp.op, temp.u.ptr);
    GNULLARY(node->op, node->u.ptr);
    GNULLARY(next->op, next->u.ptr);
}
