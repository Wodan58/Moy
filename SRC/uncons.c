/* uncons.c */
PRIVATE void uncons_()
{
    Node save;

    ONEPARAM("uncons");
    switch (stk->op) {
    case SET_:
	 {
	    int i = 0;
	    long_t set = stk->u.set;
	    CHECKEMPTYSET(set, "uncons");
	    while (!(set & (1 << i)))
		i++;
	    if (OUTSIDE) {
		stk->u.num = i;
		stk->op = INTEGER_;
	    } else
		UNARY(INTEGER_NEWNODE, i);
	    PUSH(SET_, set & ~(1 << i));
	    break;
	}
    case STRING_:
	 {
	    char *str = stk->u.str;
	    CHECKEMPTYSTRING(str, "uncons");
	    if (OUTSIDE) {
		stk->u.num = *str;
		stk->op = CHAR_;
	    } else
		UNARY(CHAR_NEWNODE, *str);
	    PUSH(STRING_, GC_strdup(++str));
	    break;
	}
    case LIST_:
	save = *stk;
	CHECKEMPTYLIST(stk->u.lis, "uncons");
	if (OUTSIDE) {
	    stk->op = stk->u.lis->op;
	    stk->u = stk->u.lis->u;
	} else
	    GUNARY(stk->u.lis->op, stk->u.lis->u);
	PUSH(LIST_, save.u.lis->next);
	return;
    default:
	BADAGGREGATE("uncons");
    }
}
