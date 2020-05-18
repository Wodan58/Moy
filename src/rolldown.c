/*
    module  : rolldown.c
    version : 1.10
    date    : 03/28/20
*/
#ifndef ROLLDOWN_C
#define ROLLDOWN_C

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
    next->u = node->u;
    next->op = node->op;
    node->u = stk->u;
    node->op = stk->op;
    stk->u = temp.u;
    stk->op = temp.op;
}
#endif
