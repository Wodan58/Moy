/*
    module  : stack.c
    version : 1.7
    date    : 07/02/18
*/

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
