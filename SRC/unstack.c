/*
    module  : unstack.c
    version : 1.4
    date    : 03/12/17
*/
#include "runtime.h"

/*
unstack  :  [X Y ..]  ->  ..Y X
The list [X Y ..] becomes the new stack.
*/
PRIVATE void do_unstack(void)
{
    Node *cur;

#ifndef NCHECK
    COMPILE;
    ONEPARAM("unstack");
    LIST("unstack");
#endif
    cur = stk->u.lis;
    stk = memory;
    for (cur = reverse(cur); cur; cur = cur->next)
	DUPLICATE(cur);
}
