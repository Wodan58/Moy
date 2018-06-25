/*
    module  : ofat.h
    version : 1.5
    date    : 04/09/17
*/
PRIVATE void PROCEDURE(void)
{
    int i, j;
    Node *cur;

#ifndef NCHECK
    unsigned op0, op1, op2, op3;

    if (optimizing) {
	op0 = pop_history(&op1);
	op2 = pop_history(&op3);
	if (op0 == LIST_ || op0 == STRING_ || op0 == SET_) {
	    if (op0 == LIST_)
		add_history(op1);
	    else if (op0 == STRING_)
		add_history(CHAR_);
	    else
		add_history(INTEGER_);
	} else {
	    if (op2 == LIST_)
		add_history(op3);
	    else if (op2 == STRING_)
		add_history(CHAR_);
	    else
		add_history(INTEGER_);
	}
    }
    if (optimizing && AGGREGATE(AGGR) && VALID(INDEX))
	;
    else
	COMPILE;
    TWOPARAMS(NAME);
    if (INDEX->op != INTEGER_ || INDEX->u.num < 0)
	execerror("non-negative integer", NAME);
#endif
    switch (AGGR->op) {
    case LIST_:
	cur = AGGR->u.lis;
#ifndef NCHECK
	CHECKEMPTYLIST(cur, NAME);
#endif
	for (i = INDEX->u.num; i > 0; i--) {
#ifndef NCHECK
	    if (!cur->next)
		INDEXTOOLARGE(NAME);
#endif
	    cur = cur->next;
	}
	if (OUTSIDE) {
	    stk->next->u = cur->u;
	    stk->next->op = cur->op;
	    POP(stk);
	} else
	    GBINARY(cur->op, cur->u.ptr);
	break;
    case STRING_:
#ifndef NCHECK
	CHECKEMPTYSTRING(AGGR->u.str, NAME);
	if (strlen(AGGR->u.str) < (size_t) INDEX->u.num)
	    INDEXTOOLARGE(NAME);
#endif
	if (OUTSIDE) {
	    stk->next->u.num = AGGR->u.str[INDEX->u.num];
	    stk->next->op = CHAR_;
	    POP(stk);
	} else
	    BINARY(CHAR_NEWNODE, AGGR->u.str[INDEX->u.num]);
	break;
    case SET_:
	j = INDEX->u.num;
#ifndef NCHECK
	CHECKEMPTYSET(AGGR->u.set, NAME);
#endif
	for (i = 0; i < SETSIZE_; i++)
	    if (AGGR->u.set & (1 << i)) {
		if (!j) {
		    if (OUTSIDE) {
			stk->next->u.num = i;
			stk->next->op = INTEGER_;
			POP(stk);
		    } else
			BINARY(INTEGER_NEWNODE, i);
		    return;
		}
		j--;
	    }
#ifndef NCHECK
	INDEXTOOLARGE(NAME);
#endif
	break;
#ifndef NCHECK
    default:
	BADAGGREGATE(NAME);
#endif
    }
}

#undef PROCEDURE
#undef NAME
#undef AGGR
#undef INDEX
