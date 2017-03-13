/*
    module  : inhas.c
    version : 1.4
    date    : 03/12/17
*/
PRIVATE void PROCEDURE(void)
{
    Node *cur;
    char *str;
    int found = 0;

#ifndef NCHECK
    if (optimizing && VALID(AGGR) && VALID(ELEM))
	;
    else
	COMPILE;
    TWOPARAMS(NAME);
#endif
    switch (AGGR->op) {
    case LIST_:
	cur = AGGR->u.lis;
	while (cur && cur->u.num != ELEM->u.num)
	    cur = cur->next;
	found = cur != 0;
	break;
    case STRING_:
	for (str = AGGR->u.str; *str && *str != ELEM->u.num; str++)
	    ;
	found = *str != 0;
	break;
    case SET_:
	found = (AGGR->u.set & (1 << ELEM->u.num)) > 0;
	break;
#ifndef NCHECK
    default:
	BADAGGREGATE(NAME);
#endif
    }
    if (OUTSIDE) {
	stk->next->u.num = found;
	stk->next->op = BOOLEAN_;
	POP(stk);
    } else
	BINARY(BOOLEAN_NEWNODE, found);
}

#undef PROCEDURE
#undef NAME
#undef AGGR
#undef ELEM
