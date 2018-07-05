/*
    module  : rollup.c
    version : 1.7
    date    : 07/05/18
*/
#ifdef RUNTIME
void do_rollup(void)
{
    node_t temp;

    TRACE;
    temp = stk[-1];
    stk[-1] = stk[-2];
    stk[-2] = stk[-3];
    stk[-3] = temp;
}
#else
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
#endif
