/*
    module  : andorxor.h
    version : 1.8
    date    : 03/28/20
*/
PRIVATE void PROCEDURE(void)
{
#ifndef OLD_RUNTIME
    if (compiling && VALID_1 && VALID_2 && stk->op == stk->next->op &&
	stk->op >= BOOLEAN_ && stk->op <= SET_)
	;
    else
	COMPILE;
#endif
    TWOPARAMS(NAME);
    SAME2TYPES(NAME);
    switch (stk->next->op) {
    case SET_:
	stk->next->u.set = stk->next->u.set OPER1 stk->u.set;
	POP(stk);
	break;
    case BOOLEAN_:
    case CHAR_:
    case INTEGER_:
    case LIST_:
	stk->next->u.num = stk->next->u.num OPER2 stk->u.num;
	stk->next->op = BOOLEAN_;
	POP(stk);
	break;
    default:
	BADDATA(NAME);
	break;
    }
}

#undef PROCEDURE
#undef NAME
#undef OPER1
#undef OPER2
