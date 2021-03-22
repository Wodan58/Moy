/*
    module  : rolldown.c
    version : 1.11
    date    : 03/15/21
*/
#ifndef ROLLDOWN_C
#define ROLLDOWN_C

/**
rolldown  :  X Y Z  ->  Y Z X
Moves Y and Z down, moves X up.
*/
PRIVATE void do_rolldown(pEnv env)
{
    Node temp, *node, *next;

#ifndef OLD_RUNTIME
    if (compiling && VALID_1 && VALID_2 && VALID_3)
	;
    else
	COMPILE;
#endif
    THREEPARAMS("rolldown");
    node = env->stk->next;
    next = node->next;
    temp = *next;
    next->u = node->u;
    next->op = node->op;
    node->u = env->stk->u;
    node->op = env->stk->op;
    env->stk->u = temp.u;
    env->stk->op = temp.op;
}
#endif
