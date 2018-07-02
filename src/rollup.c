/*
    module  : rollup.c
    version : 1.6
    date    : 07/02/18
*/

/**
rollup  :  X Y Z  ->  Z X Y
Moves X and Y up, moves Z down.
*/
PRIVATE void do_rollup(void)
{
    Node temp, *node, *next;

#ifndef NCHECK
    if (compiling && VALID_1 && VALID_2 && VALID_3)
	;
    else
	COMPILE;
#endif
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
