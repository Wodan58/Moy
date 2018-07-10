/*
    module  : equal.c
    version : 1.9
    date    : 07/10/18
*/
#ifndef EQUAL_X
#define EQUAL_C

#ifdef RUNTIME
int equal(code_t *first, code_t *second)
{
    for (; first && second; first = first->next, second = second->next) {
	if (first->num > start_of_heap && second->num > start_of_heap) {
	    if (!equal(first->list, second->list))
		return 0;
	} else if (first->num != second->num)
	    return 0;
    }
    return !first && !second;
}

void do_equal(void)
{
    TRACE;
    if (stk[-2] > start_of_heap && stk[-1] > start_of_heap)
	stk[-2] = equal((code_t *)stk[-2], (code_t *)stk[-1]);
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

/**
equal  :  T U  ->  B
(Recursively) tests whether trees T and U are identical.
*/
PRIVATE int equal_aux(Node *n1, Node *n2);

PRIVATE int equal_list_aux(Node *n1, Node *n2)
{
    if (!n1 && !n2)
	return 1;
    if (!n1 || !n2)
	return 0;
    if (equal_aux(n1, n2))
	return equal_list_aux(n1->next, n2->next);
    else
	return 0;
}

PRIVATE int equal_aux(Node *n1, Node *n2)
{
    int ok;

    if (!n1 && !n2)
	return 1;
    if (!n1 || !n2)
	return 0;
    if (n1->op == LIST_ && n2->op == LIST_)
	return equal_list_aux(n1->u.lis, n2->u.lis);
    return Compare(n1, n2, &ok) == ok;
}

PRIVATE void do_equal(void)
{
#ifndef NCHECK
    if (compiling && VALID_1 && VALID_2)
	;
    else
	COMPILE;
#endif
    TWOPARAMS("equal");
    if (OUTSIDE) {
	stk->next->u.num = equal_aux(stk, stk->next);
	stk->next->op = BOOLEAN_;
	POP(stk);
    } else
	BINARY(BOOLEAN_NEWNODE, equal_aux(stk, stk->next));
}
#endif
#endif
