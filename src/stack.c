/*
    module  : stack.c
    version : 1.12
    date    : 03/28/20
*/
#ifndef STACK_C
#define STACK_C

/**
stack  :  .. X Y Z  ->  .. X Y Z [Z Y X ..]
Pushes the stack as a list.
*/
PRIVATE void do_stack(void)
{
    Node *cur, *node = 0;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    for (cur = stk; cur; cur = cur->next)
	node = newnode(cur->op, cur->u.ptr, node);
    PUSH(LIST_, reverse(node));
}
#endif
