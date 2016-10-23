/*
    module  : unstack.c
    version : 1.3
    date    : 10/05/16
*/
#include "interp.h"

/*
unstack  :  [X Y ..]  ->  ..Y X
The list [X Y ..] becomes the new stack.
*/
/* unstack.c */
PRIVATE void unstack_(void)
{
    Node *cur;

    ONEPARAM("unstack");
    LIST("unstack");
    cur = stk->u.lis;
    stk = &memory[MEMORYMAX];
    for (cur = reverse(cur); cur; cur = cur->next)
	DUPLICATE(cur);
}
