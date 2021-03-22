/*
    module  : ofat.h
    version : 1.10
    date    : 03/15/21
*/
PRIVATE void PROCEDURE(pEnv env)
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
	env->stk->next->u = cur->u;
	env->stk->next->op = cur->op;
	POP(env->stk);
	break;
    case STRING_:
	CHECKEMPTYSTRING(AGGR->u.str, NAME);
	if (strlen(AGGR->u.str) < (size_t) INDEX->u.num)
	    INDEXTOOLARGE(NAME);
	env->stk->next->u.num = AGGR->u.str[INDEX->u.num];
	env->stk->next->op = CHAR_;
	POP(env->stk);
	break;
    case SET_:
	j = INDEX->u.num;
	CHECKEMPTYSET(AGGR->u.set, NAME);
	for (i = 0; i < SETSIZE_; i++)
	    if (AGGR->u.set & ((long_t)1 << i)) {
		if (!j) {
		    env->stk->next->u.num = i;
		    env->stk->next->op = INTEGER_;
		    POP(env->stk);
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
