/*
    module  : predsucc.c
    version : 1.3
    date    : 03/12/17
*/
PRIVATE void PROCEDURE(void)
{
#ifndef NCHECK
    if (optimizing && (INTEGER_1 || CHAR_1 || BOOLEAN_1))
	;
    else
	COMPILE;
    ONEPARAM(NAME);
    NUMERICTYPE(NAME);
#endif
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
