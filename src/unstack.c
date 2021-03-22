/*
    module  : unstack.c
    version : 1.13
    date    : 03/15/21
*/
#ifndef UNSTACK_C
#define UNSTACK_C

/**
unstack  :  [X Y ..]  ->  ..Y X
The list [X Y ..] becomes the new stack.
*/
PRIVATE void do_unstack(pEnv env)
{
    Node *cur;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM("unstack");
    LIST("unstack");
    for (cur = reverse(env->stk->u.lis), env->stk = 0; cur; cur = cur->next)
	DUPLICATE(cur);
}
#endif
