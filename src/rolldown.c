/*
    module  : rolldown.c
    version : 1.5
    date    : 06/25/18
*/
#include "runtime.h"

/**
rolldown  :  X Y Z  ->  Y Z X
Moves Y and Z down, moves X up.
*/
PRIVATE void do_rolldown(void)
{
    Node temp, *node, *next;

#ifndef NCHECK
    unsigned op0, op1, op2, op3, op4, op5;

    if (optimizing) {
	op0 = pop_history(&op1);	// Z
	op2 = pop_history(&op3);	// Y
	op4 = pop_history(&op5);	// X
	add_history2(op2, op3);		// Y
	add_history2(op0, op1);		// Z
	add_history2(op4, op5);		// X
    }
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
