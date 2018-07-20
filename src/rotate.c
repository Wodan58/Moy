/*
    module  : rotate.c
    version : 1.10
    date    : 07/20/18
*/
#ifndef ROTATE_X
#define ROTATE_C

#ifdef NEW_RUNTIME
void do_rotate(void)
{
    node_t temp;

    TRACE;
    temp = stk[-1];
    stk[-1] = stk[-3];
    stk[-3] = temp;
}
#else
/**
rotate  :  X Y Z  ->  Z Y X
Interchanges X and Z.
*/
PRIVATE void do_rotate(void)
{
    Node temp, *node, *next;

#ifndef OLD_RUNTIME
    if (compiling && VALID_1 && VALID_2 && VALID_3)
	;
    else
	COMPILE;
#endif
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
#endif
#endif
