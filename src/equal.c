/*
    module  : equal.c
    version : 1.12
    date    : 05/26/19
*/
#ifndef EQUAL_X
#define EQUAL_C

#ifdef NEW_RUNTIME
int equal_list(code_t *first, code_t *second)
{
    for (; first && second; first = first->next, second = second->next) {
	if (IS_LIST(first->num) && IS_LIST(second->num)) {
	    if (!equal_list(first->list, second->list))
		return 0;
	} else if (first->num != second->num)
	    return 0;
    }
    return !first && !second;
}

void do_equal(void)
{
    TRACE;
    if (IS_LIST(stk[-2]) && IS_LIST(stk[-1]))
	stk[-2] = equal_list((code_t *)stk[-2], (code_t *)stk[-1]);
    else
	stk[-2] = stk[-2] == stk[-1];
    (void)do_pop();
}
#else

#ifndef CASE_C
#undef CASE_X
#include "case.c"
#define CASE_X
#endif

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
    if (OUTSIDE) {
	stk->next->u.num = equal(stk, stk->next);
	stk->next->op = BOOLEAN_;
	POP(stk);
    } else
	BINARY(BOOLEAN_NEWNODE, equal(stk, stk->next));
}
#endif
#endif
