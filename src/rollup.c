/*
    module  : rollup.c
    version : 1.10
    date    : 03/28/20
*/
#ifndef ROLLUP_C
#define ROLLUP_C

/**
rollup  :  X Y Z  ->  Z X Y
Moves X and Y up, moves Z down.
*/
PRIVATE void do_rollup(void)
{
    Node temp, *node, *next;

#ifndef OLD_RUNTIME
    if (compiling && VALID_1 && VALID_2 && VALID_3)
	;
    else
	COMPILE;
#endif
    THREEPARAMS("rollup");
    temp = *stk;
    node = stk->next;
    next = node->next;
    stk->u = node->u;
    stk->op = node->op;
    node->u = next->u;
    node->op = next->op;
    next->u = temp.u;
    next->op = temp.op;
}
#endif
