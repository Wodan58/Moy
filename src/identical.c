/*
    module  : identical.c
    version : 1.1
    date    : 05/26/19
*/
#ifndef IDENTICAL_X
#define IDENTICAL_C

#ifdef NEW_RUNTIME
int identical_list(code_t *first, code_t *second)
{
    for (; first && second; first = first->next, second = second->next) {
	if (IS_LIST(first->num) && IS_LIST(second->num)) {
	    if (!identical_list(first->list, second->list))
		return 0;
	} else if (first->num != second->num)
	    return 0;
    }
    return !first && !second;
}

void do_identical(void)
{
    TRACE;
    if (IS_LIST(stk[-2]) && IS_LIST(stk[-1]))
	stk[-2] = identical_list((code_t *)stk[-2], (code_t *)stk[-1]);
    else
	stk[-2] = stk[-2] == stk[-1];
    (void)do_pop();
}
#else

PRIVATE int identical_list(Node *first, Node *second);

/**
identical  :  T U  ->  B
(Recursively) tests whether trees T and U are identical.
*/
PRIVATE int identical(Node *first, Node *second)
{
    int ok;

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

PRIVATE void do_identical(void)
{
#ifndef OLD_RUNTIME
    if (compiling && VALID_1 && VALID_2)
	;
    else
	COMPILE;
#endif
    TWOPARAMS("identical");
    if (OUTSIDE) {
	stk->next->u.num = identical(stk, stk->next);
	stk->next->op = BOOLEAN_;
	POP(stk);
    } else
	BINARY(BOOLEAN_NEWNODE, identical(stk, stk->next));
}
#endif
#endif
