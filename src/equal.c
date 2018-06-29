/*
    module  : equal.c
    version : 1.6
    date    : 06/29/18
*/
#include "runtime.h"

PRIVATE double Compare(Node *first, Node *second, int *error);

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
    if (optimizing) {
	del_history(1);
	chg_history(BOOLEAN_);
    }
    if (optimizing && VALID(stk) && VALID(stk->next))
	;
    else
	COMPILE;
    TWOPARAMS("equal");
#endif
    if (OUTSIDE) {
	stk->next->u.num = equal_aux(stk, stk->next);
	stk->next->op = BOOLEAN_;
	POP(stk);
    } else
	BINARY(BOOLEAN_NEWNODE, equal_aux(stk, stk->next));
}
