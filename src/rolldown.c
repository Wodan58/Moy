/*
    module  : rolldown.c
    version : 1.9
    date    : 07/15/18
*/
#ifndef ROLLDOWN_X
#define ROLLDOWN_C

#ifdef NEW_RUNTIME
void do_rolldown(void)
{
    node_t temp;

    TRACE;
    temp = stk[-3];
    stk[-3] = stk[-2];
    stk[-2] = stk[-1];
    stk[-1] = temp;
}
#else
/**
rolldown  :  X Y Z  ->  Y Z X
Moves Y and Z down, moves X up.
*/
PRIVATE void do_rolldown(void)
{
    Node temp, *node, *next;

#ifndef OLD_RUNTIME
    if (compiling && VALID_1 && VALID_2 && VALID_3)
	;
    else
	COMPILE;
#endif
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
#endif
#endif
