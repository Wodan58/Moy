/*
    module  : predsucc.h
    version : 1.4
    date    : 07/02/18
*/
PRIVATE void PROCEDURE(void)
{
#ifndef NCHECK
    if (compiling && (INTEGER_1 || CHAR_1 || BOOLEAN_1))
	;
    else
	COMPILE;
#endif
    ONEPARAM(NAME);
    NUMERICTYPE(NAME);
    if (OUTSIDE)
	stk->u.num = stk->u.num OPER 1;
    else if (stk->op == CHAR_)
	UNARY(CHAR_NEWNODE, stk->u.num OPER 1);
    else
	UNARY(INTEGER_NEWNODE, stk->u.num OPER 1);
}

#undef PROCEDURE
#undef NAME
#undef OPER
