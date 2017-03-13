/*
    module  : stack.c
    version : 1.4
    date    : 03/12/17
*/
#include "runtime.h"

/*
stack  :  .. X Y Z  ->  .. X Y Z [Z Y X ..]
Pushes the stack as a list.
*/
PRIVATE void do_stack(void)
{
    Node *cur, *node = 0;

#ifndef NCHECK
    COMPILE;
#endif
    for (cur = stk; cur != memory; cur = cur->next)
	node = heapnode(cur->op, cur->u.ptr, node);
    PUSH(LIST_, reverse(node));
}
