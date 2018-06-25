/*
    module  : stack.c
    version : 1.6
    date    : 06/25/18
*/
#include "runtime.h"

/**
stack  :  .. X Y Z  ->  .. X Y Z [Z Y X ..]
Pushes the stack as a list.
*/
PRIVATE void do_stack(void)
{
    Node *cur, *node = 0;

#ifndef NCHECK
    if (optimizing)
	add_history(LIST_);
    COMPILE;
#endif
    for (cur = stk; cur != memory; cur = cur->next)
	node = heapnode(cur->op, cur->u.ptr, node);
    PUSH(LIST_, reverse(node));
}
