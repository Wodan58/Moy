/*
    module  : unstack.c
    version : 1.8
    date    : 07/05/18
*/
#ifdef RUNTIME
void do_unstack(void)
{
    TRACE;
    lst2stk((code_t *)do_pop());
}
#else
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
#endif
