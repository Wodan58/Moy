/*
    module  : swap.c
    version : 1.5
    date    : 06/25/18
*/
#include "runtime.h"

/**
swap  :  X Y  ->  Y X
Interchanges X and Y on top of the stack.
*/
PRIVATE void do_swap(void)
{
    Node temp, *node;

#ifndef NCHECK
    unsigned op0, op1, op2, op3;

    if (optimizing) {
	op0 = pop_history(&op1);	// Y
	op2 = pop_history(&op3);	// X
	add_history2(op0, op1);		// Y
	add_history2(op2, op3);		// X
    }
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
