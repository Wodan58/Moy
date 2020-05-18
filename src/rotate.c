/*
    module  : rotate.c
    version : 1.11
    date    : 03/28/20
*/
#ifndef ROTATE_C
#define ROTATE_C

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
    stk->u = next->u;
    stk->op = next->op;
    next->u = temp.u;
    next->op = temp.op;
}
#endif
