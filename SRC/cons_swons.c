/* cons_swons.c */
PRIVATE void PROCEDURE()
{
    TWOPARAMS(NAME);
    switch (AGGR->op) {
    case LIST_:
	if (OUTSIDE) {
	    stk->next->u.lis = newnode(ELEM->op, ELEM->u, AGGR->u.lis);
	    stk->next->op = LIST_;
	    POP(stk);
	} else
	    BINARY(LIST_NEWNODE, newnode(ELEM->op, ELEM->u, AGGR->u.lis));
	break;
    case SET_:
	CHECKSETMEMBER(ELEM, NAME);
	if (OUTSIDE) {
	    stk->next->u.set = AGGR->u.set | (1 << ELEM->u.num);
	    stk->next->op = SET_;
	    POP(stk);
	} else
	    BINARY(SET_NEWNODE, AGGR->u.set | (1 << ELEM->u.num));
	break;
    case STRING_:
	{
	    char *str = GC_malloc(strlen(AGGR->u.str) + 2);
	    if (ELEM->op != CHAR_)
		execerror("character", NAME);
	    str[0] = ELEM->u.num;
	    strcpy(str + 1, AGGR->u.str);
	    if (OUTSIDE) {
		stk->next->u.str = str;
		stk->next->op = STRING_;
		POP(stk);
	    } else
		BINARY(STRING_NEWNODE, str);
	    break;
	}
    default:
	BADAGGREGATE(NAME);
    }
}

#undef PROCEDURE
#undef NAME
#undef AGGR
#undef ELEM
