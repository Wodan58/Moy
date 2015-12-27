/* drop.c */
PRIVATE void drop_()
{
    int n = stk->u.num;

    TWOPARAMS("drop");
    switch (stk->next->op) {
    case SET_:
	 {
	    int i;
	    long_t result = 0;
	    for (i = 0; i < SETSIZE; i++)
		if (stk->next->u.set & (1 << i)) {
		    if (n < 1)
			result |= 1 << i;
		    else
			n--;
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
	    char *result = stk->next->u.str;
	    while (n-- > 0 && *result)
		++result;
	    if (OUTSIDE) {
		stk->next->u.str = result;
		POP(stk);
	    } else
		BINARY(STRING_NEWNODE, result);
	    return;
	}
    case LIST_:
	 {
	    Node *result = stk->next->u.lis;
	    while (n-- > 0 && result)
		result = result->next;
	    if (OUTSIDE) {
		stk->next->u.lis = result;
		POP(stk);
	    } else
		BINARY(LIST_NEWNODE, result);
	    return;
	}
    default:
	BADAGGREGATE("drop");
    }
}
