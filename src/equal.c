/*
    module  : equal.c
    version : 1.15
    date    : 06/20/22
*/
#ifndef EQUAL_C
#define EQUAL_C

#include "compare.h"

/**
equal  :  T U  ->  B
(Recursively) tests whether trees T and U are identical.
*/
PRIVATE int equal(pEnv env, Node *first, Node *second);

PRIVATE int equal_list(pEnv env, Node *first, Node *second)
{
    for (; first && second; first = first->next, second = second->next)
	if (!equal(env, first, second))
	    return 0;
    return !first && !second;
}

PRIVATE int equal(pEnv env, Node *first, Node *second)
{
    if (first->op == LIST_ && second->op == LIST_)
	return equal_list(env, first->u.lis, second->u.lis);
    return !Compare(env, first, second);
}

PRIVATE void do_equal(pEnv env)
{
    TWOPARAMS("equal");
    BINARY(BOOLEAN_NEWNODE, equal(env, env->stk, env->stk->next));
}
#endif
