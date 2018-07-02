/*
    module  : equal.c
    version : 1.7
    date    : 07/02/18
*/

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
