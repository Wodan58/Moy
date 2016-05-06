/*
    module  : equal.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
equal  :  T U  ->  B
(Recursively) tests whether trees T and U are identical.
*/
/* equal.c */
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
    int error;

    if (!n1 && !n2)
	return 1;
    if (!n1 || !n2)
	return 0;
    if (n1->op == LIST_ && n2->op == LIST_)
	return equal_list_aux(n1->u.lis, n2->u.lis);
    return !Compare(n1, n2, &error) && !error;
}

PRIVATE void equal_(void)
{
    TWOPARAMS("equal");
    if (OUTSIDE) {
	stk->next->u.num = equal_aux(stk, stk->next);
	stk->next->op = BOOLEAN_;
	POP(stk);
    } else
	BINARY(BOOLEAN_NEWNODE, equal_aux(stk, stk->next));
}
