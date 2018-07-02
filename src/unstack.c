/*
    module  : unstack.c
    version : 1.7
    date    : 07/02/18
*/

/**
unstack  :  [X Y ..]  ->  ..Y X
The list [X Y ..] becomes the new stack.
*/
PRIVATE void do_unstack(void)
{
    Node *cur;

#ifndef NCHECK
    COMPILE;
#endif
    ONEPARAM("unstack");
    LIST("unstack");
    for (cur = reverse(stk->u.lis), stk = 0; cur; cur = cur->next)
	DUPLICATE(cur);
}
