/* rest.c */
PRIVATE void rest_()
{
    ONEPARAM("rest");
    switch (stk->op) {
    case SET_:
	 {
	    int i = 0;
	    CHECKEMPTYSET(stk->u.set, "rest");
	    while (!(stk->u.set & (1 << i)))
		i++;
	    if (OUTSIDE)
		stk->u.set = stk->u.set & ~(1 << i);
	    else
		UNARY(SET_NEWNODE, stk->u.set & ~(1 << i));
	    break;
	}
    case STRING_:
	 {
	    char *str = stk->u.str;
	    CHECKEMPTYSTRING(str, "rest");
	    if (OUTSIDE)
		stk->u.str = GC_strdup(++str);
	    else
		UNARY(STRING_NEWNODE, GC_strdup(++str));
	    break;
	}
    case LIST_:
	CHECKEMPTYLIST(stk->u.lis, "rest");
	if (OUTSIDE)
	    stk->u.lis = stk->u.lis->next;
	else
	    UNARY(LIST_NEWNODE, stk->u.lis->next);
	return;
    default:
	BADAGGREGATE("rest");
    }
}
