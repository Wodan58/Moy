/*
    module  : stack.c
    version : 1.3
    date    : 10/04/16
*/
#include "interp.h"

/*
stack  :  .. X Y Z  ->  .. X Y Z [Z Y X ..]
Pushes the stack as a list.
*/
/* stack.c */
PRIVATE void stack_(void)
{
    Node *cur, *node = 0;

    for (cur = stk; cur && cur != &memory[MEMORYMAX]; cur = cur->next)
	node = heapnode(cur->op, cur->u.ptr, node);
    PUSH(LIST_, reverse(node));
}
