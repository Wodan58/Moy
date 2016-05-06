/*
    module  : unstack.c
    version : 1.2
    date    : 05/06/16
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
    stk = &memory[MEMORYMAX];
    for (cur = reverse(stk->u.lis); cur; cur = cur->next)
	DUPLICATE(cur);
}
