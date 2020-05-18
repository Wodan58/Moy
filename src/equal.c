/*
    module  : equal.c
    version : 1.13
    date    : 03/28/20
*/
#ifndef EQUAL_C
#define EQUAL_C

#ifdef CASE_X
#undef CASE_X
#undef CASE_C
#endif

#include "case.c"

PRIVATE int equal_list(Node *first, Node *second);

/**
equal  :  T U  ->  B
(Recursively) tests whether trees T and U are identical.
*/
PRIVATE int equal(Node *first, Node *second)
{
    int ok;

    if (!first && !second)
	return 1;
    if (!first || !second)
	return 0;
    if (first->op == LIST_ && second->op == LIST_)
	return equal_list(first->u.lis, second->u.lis);
    return Compare(first, second, &ok) == ok;
}

PRIVATE int equal_list(Node *first, Node *second)
{
    for (; first && second; first = first->next, second = second->next)
	if (!equal(first, second))
	    return 0;
    return !first && !second;
}

PRIVATE void do_equal(void)
{
#ifndef OLD_RUNTIME
    if (compiling && VALID_1 && VALID_2)
	;
    else
	COMPILE;
#endif
    TWOPARAMS("equal");
    stk->next->u.num = equal(stk, stk->next);
    stk->next->op = BOOLEAN_;
    POP(stk);
}
#endif
