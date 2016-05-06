/*
    module  : stack.c
    version : 1.2
    date    : 05/06/16
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

    for (cur = stk; cur != &memory[MEMORYMAX]; cur = cur->next)
	node = newnode(cur->op, cur->u.ptr, node);
    PUSH(LIST_, reverse(node));
}
