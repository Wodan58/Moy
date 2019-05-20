/*
    module  : stack.c
    version : 1.11
    date    : 05/18/19
*/
#ifndef STACK_X
#define STACK_C

#ifdef NEW_RUNTIME
void do_stack(void)
{
    TRACE;
    do_push((node_t)stk2lst());
}
#else
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
#endif
