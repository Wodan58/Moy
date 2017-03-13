/*
    module  : andorxor.c
    version : 1.3
    date    : 03/12/17
*/
PRIVATE void PROCEDURE(void)
{
#ifndef NCHECK
    if (optimizing && stk->op == stk->next->op &&
	stk->op >= BOOLEAN_ && stk->op <= SET_)
	;
    else
	COMPILE;
    TWOPARAMS(NAME);
    SAME2TYPES(NAME);
#endif
    switch (stk->next->op) {
    case SET_:
	if (OUTSIDE) {
	    stk->next->u.set = stk->next->u.set OPER1 stk->u.set;
	    POP(stk);
	} else
	    BINARY(SET_NEWNODE, stk->next->u.set OPER1 stk->u.set);
	break;
    case BOOLEAN_:
    case CHAR_:
    case INTEGER_:
    case LIST_:
	if (OUTSIDE) {
	    stk->next->u.num = stk->next->u.num OPER2 stk->u.num;
	    stk->next->op = BOOLEAN_;
	    POP(stk);
	} else
	    BINARY(BOOLEAN_NEWNODE, stk->next->u.num OPER2 stk->u.num);
	break;
#ifndef NCHECK
    default:
	BADDATA(NAME);
#endif
    }
}

#undef PROCEDURE
#undef NAME
#undef OPER1
#undef OPER2
