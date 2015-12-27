/* inhas.c */
PRIVATE void PROCEDURE()
{
#ifdef CORRECT_INHAS_COMPARE
    int error;
#endif
    int found = 0;

    TWOPARAMS(NAME);
    switch (AGGR->op) {
    case SET_:
	found = (AGGR->u.set & (1 << ELEM->u.num)) > 0;
	break;
    case STRING_:
	{
	    char *str;
	    for (str = AGGR->u.str;
		 str && *str && *str != ELEM->u.num; str++);
	    found = str && *str;
	    break;
	}
    case LIST_:
	{
	    Node *cur = AGGR->u.lis;
#ifdef CORRECT_INHAS_COMPARE
	    while (cur && (Compare(cur, ELEM, &error) || error))
#else
	    while (cur && cur->u.num != ELEM->u.num)
#endif
		cur = cur->next;
	    found = cur != 0;
	    break;
	}
    default:
	BADAGGREGATE(NAME);
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
