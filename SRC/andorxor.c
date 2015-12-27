/* andorxor.c */
PRIVATE void PROCEDURE()
{
    TWOPARAMS(NAME);
    SAME2TYPES(NAME);
    switch (stk->next->op) {
    case SET_:
	if (OUTSIDE) {
	    stk->next->u.set = stk->next->u.set OPER1 stk->u.set;
	    POP(stk);
	} else
	    BINARY(SET_NEWNODE, (stk->next->u.set OPER1 stk->u.set));
	return;
    case BOOLEAN_:
    case CHAR_:
    case INTEGER_:
    case LIST_:
	if (OUTSIDE) {
	    stk->next->u.num = stk->next->u.num OPER2 stk->u.num;
	    stk->next->op = BOOLEAN_;
	    POP(stk);
	} else
	    BINARY(BOOLEAN_NEWNODE, (stk->next->u.num OPER2 stk->u.num));
	return;
    default:
	BADDATA(NAME);
    }
}

#undef PROCEDURE
#undef NAME
#undef OPER1
#undef OPER2
