/*
    module  : cons_swons.c
    version : 1.4
    date    : 10/04/16
*/
/* cons_swons.c */
PRIVATE void PROCEDURE(void)
{
    TWOPARAMS(NAME);
    switch (AGGR->op) {
    case LIST_:
	if (OUTSIDE) {
	    stk->next->u.lis = heapnode(ELEM->op, ELEM->u.ptr, AGGR->u.lis);
	    stk->next->op = LIST_;
	    POP(stk);
	} else
	    BINARY(LIST_NEWNODE, heapnode(ELEM->op, ELEM->u.ptr, AGGR->u.lis));
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
	    char *str = malloc(strlen(AGGR->u.str) + 2);
#ifdef RUNTIME_CHECKS
	    if (ELEM->op != CHAR_)
		execerror("character", NAME);
#endif
	    str[0] = (char)ELEM->u.num;
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
