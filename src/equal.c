/*
    module  : equal.c
    version : 1.14
    date    : 03/15/21
*/
#ifndef EQUAL_C
#define EQUAL_C

#ifdef CASE_X
#undef CASE_X
#undef CASE_C
#endif

#include "case.c"

PRIVATE int equal_list(pEnv env, Node *first, Node *second);

/**
equal  :  T U  ->  B
(Recursively) tests whether trees T and U are identical.
*/
PRIVATE int equal(pEnv env, Node *first, Node *second)
{
    int ok;

    if (!first && !second)
	return 1;
    if (!first || !second)
	return 0;
    if (first->op == LIST_ && second->op == LIST_)
	return equal_list(env, first->u.lis, second->u.lis);
    return Compare(env, first, second, &ok) == ok;
}

PRIVATE int equal_list(pEnv env, Node *first, Node *second)
{
    for (; first && second; first = first->next, second = second->next)
	if (!equal(env, first, second))
	    return 0;
    return !first && !second;
}

PRIVATE void do_equal(pEnv env)
{
#ifndef OLD_RUNTIME
    if (compiling && VALID_1 && VALID_2)
	;
    else
	COMPILE;
#endif
    TWOPARAMS("equal");
    env->stk->next->u.num = equal(env, env->stk, env->stk->next);
    env->stk->next->op = BOOLEAN_;
    POP(env->stk);
}
#endif
