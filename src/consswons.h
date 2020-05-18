/*
    module  : consswons.h
    version : 1.11
    date    : 03/28/20
*/
PRIVATE void PROCEDURE(void)
{
    char *str;

#ifndef OLD_RUNTIME
    if (compiling && VALID_2)
	;
    else
	COMPILE;
#endif
    TWOPARAMS(NAME);
    switch (AGGR->op) {
    case LIST_:
	stk->next->u.lis = newnode(ELEM->op, ELEM->u.ptr, AGGR->u.lis);
	stk->next->op = LIST_;
	POP(stk);
	break;
    case STRING_:
#ifndef NCHECK
	if (ELEM->op != CHAR_)
	    execerror("character", NAME);
#endif
	str = ck_malloc_sec(strlen(AGGR->u.str) + 2);
	str[0] = (char)ELEM->u.num;
	strcpy(str + 1, AGGR->u.str);
	stk->next->u.str = str;
	stk->next->op = STRING_;
	POP(stk);
	break;
    case SET_:
	CHECKSETMEMBER(ELEM, NAME);
	stk->next->u.set = AGGR->u.set | ((long_t)1 << ELEM->u.num);
	stk->next->op = SET_;
	POP(stk);
	break;
    default:
	BADAGGREGATE(NAME);
	break;
    }
}

#undef PROCEDURE
#undef NAME
#undef AGGR
#undef ELEM
