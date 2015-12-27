/* first.c */
PRIVATE void first_()
{
    ONEPARAM("first");
    switch (stk->op) {
    case LIST_:
	CHECKEMPTYLIST(stk->u.lis, "first");
	if (OUTSIDE) {
	    stk->op = stk->u.lis->op;
	    stk->u = stk->u.lis->u;
	} else
	    GUNARY(stk->u.lis->op, stk->u.lis->u);
	return;
    case STRING_:
	CHECKEMPTYSTRING(stk->u.str, "first");
	if (OUTSIDE) {
	    stk->u.num = *stk->u.str;
	    stk->op = CHAR_;
	} else
	    UNARY(CHAR_NEWNODE, *stk->u.str);
	return;
    case SET_:
	 {
	    int i = 0;
	    CHECKEMPTYSET(stk->u.set, "first");
	    while (!(stk->u.set & (1 << i)))
		i++;
	    if (OUTSIDE) {
		stk->u.num = i;
		stk->op = INTEGER_;
	    } else
		UNARY(INTEGER_NEWNODE, i);
	    return;
	}
    default:
	BADAGGREGATE("first");
    }
}
