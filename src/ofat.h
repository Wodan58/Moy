/*
    module  : ofat.h
    version : 1.9
    date    : 03/28/20
*/
PRIVATE void PROCEDURE(void)
{
    int i, j;
    Node *cur;

#ifndef OLD_RUNTIME
    if (compiling && VALID_1 && VALID_2)
	;
    else
	COMPILE;
#endif
    TWOPARAMS(NAME);
#ifndef NCHECK
    if (INDEX->op != INTEGER_ || INDEX->u.num < 0)
	execerror("non-negative integer", NAME);
#endif
    switch (AGGR->op) {
    case LIST_:
	cur = AGGR->u.lis;
	CHECKEMPTYLIST(cur, NAME);
	for (i = INDEX->u.num; i > 0; i--) {
	    if (!cur->next)
		INDEXTOOLARGE(NAME);
	    cur = cur->next;
	}
	stk->next->u = cur->u;
	stk->next->op = cur->op;
	POP(stk);
	break;
    case STRING_:
	CHECKEMPTYSTRING(AGGR->u.str, NAME);
	if (strlen(AGGR->u.str) < (size_t) INDEX->u.num)
	    INDEXTOOLARGE(NAME);
	stk->next->u.num = AGGR->u.str[INDEX->u.num];
	stk->next->op = CHAR_;
	POP(stk);
	break;
    case SET_:
	j = INDEX->u.num;
	CHECKEMPTYSET(AGGR->u.set, NAME);
	for (i = 0; i < SETSIZE_; i++)
	    if (AGGR->u.set & ((long_t)1 << i)) {
		if (!j) {
		    stk->next->u.num = i;
		    stk->next->op = INTEGER_;
		    POP(stk);
		    return;
		}
		j--;
	    }
	INDEXTOOLARGE(NAME);
	break;
    default:
	BADAGGREGATE(NAME);
	break;
    }
}

#undef PROCEDURE
#undef NAME
#undef AGGR
#undef INDEX
