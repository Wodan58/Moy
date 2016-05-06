/*
    module  : rotate.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
rotate  :  X Y Z  ->  Z Y X
Interchanges X and Z.
*/
/* rotate.c */
PRIVATE void rotate_(void)
{
    Node temp, *node, *next;

    THREEPARAMS("rotate");
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
