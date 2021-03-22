/*
    module  : identical.c
    version : 1.4
    date    : 03/15/21
*/
#ifndef IDENTICAL_C
#define IDENTICAL_C

PRIVATE int identical_list(Node *first, Node *second);

/**
identical  :  T U  ->  B
(Recursively) tests whether trees T and U are identical.
*/
PRIVATE int identical(Node *first, Node *second)
{
    if (!first && !second)
	return 1;
    if (!first || !second)
	return 0;
    if (first->op != second->op)
	return 0;
    if (first->op == LIST_ && second->op == LIST_)
	return identical_list(first->u.lis, second->u.lis);
    return first->u.num == second->u.num;
}

PRIVATE int identical_list(Node *first, Node *second)
{
    for (; first && second; first = first->next, second = second->next)
	if (!identical(first, second))
	    return 0;
    return !first && !second;
}

PRIVATE void do_identical(pEnv env)
{
#ifndef OLD_RUNTIME
    if (compiling && VALID_1 && VALID_2)
	;
    else
	COMPILE;
#endif
    TWOPARAMS("identical");
    env->stk->next->u.num = identical(env->stk, env->stk->next);
    env->stk->next->op = BOOLEAN_;
    POP(env->stk);
}
#endif
