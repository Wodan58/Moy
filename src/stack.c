/*
    module  : stack.c
    version : 1.13
    date    : 03/15/21
*/
#ifndef STACK_C
#define STACK_C

/**
stack  :  .. X Y Z  ->  .. X Y Z [Z Y X ..]
Pushes the stack as a list.
*/
PRIVATE void do_stack(pEnv env)
{
    Node *cur, *node = 0;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    for (cur = env->stk; cur; cur = cur->next)
	node = newnode(cur->op, cur->u, node);
    PUSH_PTR(LIST_, reverse(node));
}
#endif
