/*
    module  : rotate.c
    version : 1.4
    date    : 04/09/17
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
    unsigned op0, op1, op2, op3, op4, op5;

    if (optimizing) {
	op0 = pop_history(&op1);	// Z
	op2 = pop_history(&op3);	// Y
	op4 = pop_history(&op5);	// X
	add_history2(op0, op1);		// Z
	add_history2(op2, op3);		// Y
	add_history2(op4, op5);		// X
    }
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
