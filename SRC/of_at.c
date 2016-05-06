/*
    module  : of_at.c
    version : 1.2
    date    : 05/06/16
*/
/* of_at.c */
PRIVATE void PROCEDURE(void)
{
    int i;

    TWOPARAMS(NAME);
#ifdef RUNTIME_CHECKS
    if (INDEX->op != INTEGER_ || INDEX->u.num < 0)
	execerror("non-negative integer", NAME);
#endif
    switch (AGGR->op) {
    case SET_:
	{
	    int indx = INDEX->u.num;
	    CHECKEMPTYSET(AGGR->u.set, NAME);
	    for (i = 0; i < SETSIZE; i++)
		if (AGGR->u.set & (1 << i)) {
		    if (!indx) {
			if (OUTSIDE) {
			    stk->next->u.num = i;
			    stk->next->op = INTEGER_;
			    POP(stk);
			} else
			    BINARY(INTEGER_NEWNODE, i);
			return;
		    }
		    indx--;
		}
	    INDEXTOOLARGE(NAME);
	    return;
	}
    case STRING_:
	if (strlen(AGGR->u.str) < (size_t) INDEX->u.num)
	    INDEXTOOLARGE(NAME);
	if (OUTSIDE) {
	    stk->next->u.num = AGGR->u.str[INDEX->u.num];
	    stk->next->op = CHAR_;
	    POP(stk);
	} else
	    BINARY(CHAR_NEWNODE, AGGR->u.str[INDEX->u.num]);
	return;
    case LIST_:
	{
	    Node *cur = AGGR->u.lis;
	    CHECKEMPTYLIST(cur, NAME);
	    for (i = INDEX->u.num; i > 0; i--) {
		if (!cur->next)
		    INDEXTOOLARGE(NAME);
		cur = cur->next;
	    }
	    if (OUTSIDE) {
		stk->next->u = cur->u;
		stk->next->op = cur->op;
		POP(stk);
	    } else
		GBINARY(cur->op, cur->u.ptr);
	    return;
	}
    default:
	BADAGGREGATE(NAME);
    }
}

#undef PROCEDURE
#undef NAME
#undef AGGR
#undef INDEX
