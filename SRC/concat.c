/* concat.c */
PRIVATE void concat_()
{
    Node *cur = 0;
    Node *root = 0;
    Node *last = 0;

    TWOPARAMS("concat");
    SAME2TYPES("concat");
    switch (stk->op) {
    case SET_:
	if (OUTSIDE) {
	    stk->next->u.set |= stk->u.set;
	    POP(stk);
	} else
	    BINARY(SET_NEWNODE, stk->next->u.set | stk->u.set);
	return;
    case STRING_:
	 {
	    char *str = GC_malloc(strlen(stk->next->u.str) +
				  strlen(stk->u.str) + 1);
	    strcpy(str, stk->next->u.str);
	    strcat(str, stk->u.str);
	    if (OUTSIDE) {
		stk->next->u.str = str;
		POP(stk);
	    } else
		BINARY(STRING_NEWNODE, str);
	    return;
	}
    case LIST_:
	if (!stk->next->u.lis) {
	    if (OUTSIDE) {
		stk->next->u.lis = stk->u.lis;
		POP(stk);
	    } else
	        BINARY(LIST_NEWNODE, stk->u.lis);
	    return;
	}
	for (cur = stk->next->u.lis; cur; cur = cur->next)
	    if (!root)
		last = root = newnode(cur->op, cur->u, 0);
	    else
		last = last->next = newnode(cur->op, cur->u, 0);
	last->next = stk->u.lis;
	if (OUTSIDE) {
	    stk->next->u.lis = root;
	    POP(stk);
	} else
	    BINARY(LIST_NEWNODE, root);
	return;
    default:
	BADAGGREGATE("concat");
    }
}
