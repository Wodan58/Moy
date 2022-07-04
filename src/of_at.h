/*
    module  : of_at.h
    version : 1.11
    date    : 06/20/22
*/
PRIVATE void PROCEDURE(pEnv env)
{
    int i, j;
    Node *cur;

    TWOPARAMS(NAME);
    POSITIVEINDEX(INDEX, NAME);
    switch (AGGR->op) {
    case LIST_:
	cur = AGGR->u.lis;
	CHECKEMPTYLIST(cur, NAME);
	for (i = INDEX->u.num; i > 0; i--) {
	    if (!cur->next)
		INDEXTOOLARGE(NAME);
	    cur = cur->next;
	}
	GBINARY(cur->op, cur->u);
	break;
    case STRING_:
	CHECKEMPTYSTRING(AGGR->u.str, NAME);
	if (strlen(AGGR->u.str) < (size_t) INDEX->u.num)
	    INDEXTOOLARGE(NAME);
	BINARY(CHAR_NEWNODE, AGGR->u.str[INDEX->u.num]);
	break;
    case SET_:
	j = INDEX->u.num;
	CHECKEMPTYSET(AGGR->u.set, NAME);
	for (i = 0; i < SETSIZE_; i++)
	    if (AGGR->u.set & ((long)1 << i)) {
		if (!j) {
		    BINARY(INTEGER_NEWNODE, i);
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
