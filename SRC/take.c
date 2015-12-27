/* take.c */
PRIVATE void take_()
{
    Node *cur = 0;
    Node *root = 0;
    Node *last = 0;
    int i = stk->u.num, n = stk->u.num;

    TWOPARAMS("take");
    switch (stk->next->op) {
    case SET_:
	{
	    long_t result = 0;
	    for (i = 0; i < SETSIZE; i++)
		if (stk->next->u.set & (1 << i)) {
		    if (n > 0) {
			result |= 1 << i;
			--n;
		    } else
			break;
		}
	    if (OUTSIDE) {
		stk->next->u.set = result;
		POP(stk);
	    } else
		BINARY(SET_NEWNODE, result);
	    return;
	}
    case STRING_:
	{
	    char *ptr, *result;
	    char *old = stk->next->u.str;
	    POP(stk);
	    if (i < 0)
		i = 0;
	    if ((size_t) i > strlen(old))
		return;
	    ptr = result = GC_malloc(i + 1);
	    while (i-- > 0)
		*ptr++ = *old++;
	    *ptr = 0;
	    if (OUTSIDE) {
		stk->next->u.str = result;
		POP(stk);
	    } else
		UNARY(STRING_NEWNODE, result);
	    return;
	}
    case LIST_:
	{
	    if (i < 1) {
		if (OUTSIDE) {
		    stk->next->u.lis = 0;
		    POP(stk);
		} else
		    BINARY(LIST_NEWNODE, 0);
		return;
	    }
	    for (cur = stk->next->u.lis; cur && i-- > 0; cur = cur->next) {
		if (!root)
		    last = root = newnode(cur->op, cur->u, 0);
		else
		    last = last->next = newnode(cur->op, cur->u, 0);
	    }
	    if (OUTSIDE) {
		stk->next->u.lis = root;
		POP(stk);
	    } else
		BINARY(LIST_NEWNODE, root);
	    return;
	}
    default:
	BADAGGREGATE("take");
    }
}
