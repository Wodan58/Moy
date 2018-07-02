/*
    module  : rotate.c
    version : 1.6
    date    : 07/02/18
*/

/**
rotate  :  X Y Z  ->  Z Y X
Interchanges X and Z.
*/
PRIVATE void do_rotate(void)
{
    Node temp, *node, *next;

#ifndef NCHECK
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
