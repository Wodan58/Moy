/*
    module  : rollup.c
    version : 1.11
    date    : 03/15/21
*/
#ifndef ROLLUP_C
#define ROLLUP_C

/**
rollup  :  X Y Z  ->  Z X Y
Moves X and Y up, moves Z down.
*/
PRIVATE void do_rollup(pEnv env)
{
    Node temp, *node, *next;

#ifndef OLD_RUNTIME
    if (compiling && VALID_1 && VALID_2 && VALID_3)
	;
    else
	COMPILE;
#endif
    THREEPARAMS("rollup");
    temp = *env->stk;
    node = env->stk->next;
    next = node->next;
    env->stk->u = node->u;
    env->stk->op = node->op;
    node->u = next->u;
    node->op = next->op;
    next->u = temp.u;
    next->op = temp.op;
}
#endif
