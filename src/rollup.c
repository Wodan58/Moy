/*
    module  : rollup.c
    version : 1.5
    date    : 06/25/18
*/
#include "runtime.h"

/**
rollup  :  X Y Z  ->  Z X Y
Moves X and Y up, moves Z down.
*/
PRIVATE void do_rollup(void)
{
    Node temp, *node, *next;

#ifndef NCHECK
    unsigned op0, op1, op2, op3, op4, op5;

    if (optimizing) {
	op0 = pop_history(&op1);	// Z
	op2 = pop_history(&op3);	// Y
	op4 = pop_history(&op5);	// X
	add_history2(op0, op1);		// Z
	add_history2(op4, op5);		// X
	add_history2(op2, op3);		// Y
    }
    if (optimizing && VALID(stk) && VALID(stk->next) && VALID(stk->next->next))
	;
    else
	COMPILE;
    THREEPARAMS("rollup");
#endif
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
