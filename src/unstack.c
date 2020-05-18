/*
    module  : unstack.c
    version : 1.12
    date    : 03/28/20
*/
#ifndef UNSTACK_C
#define UNSTACK_C

/**
unstack  :  [X Y ..]  ->  ..Y X
The list [X Y ..] becomes the new stack.
*/
PRIVATE void do_unstack(void)
{
    Node *cur;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM("unstack");
    LIST("unstack");
    for (cur = reverse(stk->u.lis), stk = 0; cur; cur = cur->next)
	DUPLICATE(cur);
}
#endif
