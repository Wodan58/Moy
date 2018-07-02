/*
    module  : ofat.h
    version : 1.6
    date    : 07/02/18
*/
PRIVATE void PROCEDURE(void)
{
    int i, j;
    Node *cur;

#ifndef NCHECK
    if (compiling && VALID_1 && VALID_2)
	;
    else
	COMPILE;
#endif
    TWOPARAMS(NAME);
    if (INDEX->op != INTEGER_ || INDEX->u.num < 0)
	execerror("non-negative integer", NAME);
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
