/*
    module  : rotate.c
    version : 1.12
    date    : 03/15/21
*/
#ifndef ROTATE_C
#define ROTATE_C

/**
rotate  :  X Y Z  ->  Z Y X
Interchanges X and Z.
*/
PRIVATE void do_rotate(pEnv env)
{
    Node temp, *node, *next;

#ifndef OLD_RUNTIME
    if (compiling && VALID_1 && VALID_2 && VALID_3)
	;
    else
	COMPILE;
#endif
    THREEPARAMS("rotate");
    temp = *env->stk;
    node = env->stk->next;
    next = node->next;
    env->stk->u = next->u;
    env->stk->op = next->op;
    next->u = temp.u;
    next->op = temp.op;
}
#endif
