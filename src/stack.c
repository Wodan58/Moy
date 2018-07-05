/*
    module  : stack.c
    version : 1.8
    date    : 07/05/18
*/
#ifdef RUNTIME
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

#ifndef NCHECK
    COMPILE;
#endif
    for (cur = stk; cur; cur = cur->next)
	node = heapnode(cur->op, cur->u.ptr, node);
    PUSH(LIST_, reverse(node));
}
#endif
