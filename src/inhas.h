/*
    module  : inhas.h
    version : 1.9
    date    : 07/15/18
*/
PRIVATE void PROCEDURE(void)
{
    Node *cur;
    char *str;
    int found = 0;
#ifdef CORRECT_INHAS_COMPARE
    int ok;
#endif

#ifndef OLD_RUNTIME
    if (compiling && VALID_1 && VALID_2)
	;
    else
	COMPILE;
#endif
    TWOPARAMS(NAME);
    switch (AGGR->op) {
    case LIST_:
	for (cur = AGGR->u.lis; cur; cur = cur->next)
#ifdef CORRECT_INHAS_COMPARE
	    if (Compare(cur, ELEM, &ok) == ok)
#else
	    if (cur->u.num == ELEM->u.num)
#endif
		break;
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
    default:
	BADAGGREGATE(NAME);
	break;
    }
    if (OUTSIDE) {
	stk->next->u.num = found;
	stk->next->op = BOOLEAN_;
	POP(stk);
    } else
	BINARY(BOOLEAN_NEWNODE, found);
}

#undef PROCEDURE
#ifdef CORRECT_INHAS_COMPARE
#undef CORRECT_INHAS_COMPARE
#endif
#undef NAME
#undef AGGR
#undef ELEM
