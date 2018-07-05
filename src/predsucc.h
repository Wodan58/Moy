/*
    module  : predsucc.h
    version : 1.5
    date    : 07/05/18
*/
PRIVATE void PROCEDURE(void)
{
#ifdef RUNTIME
    TRACE;
    stk[-1] = stk[-1] OPER 1;
#else
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
#endif
}

#undef PROCEDURE
#undef NAME
#undef OPER
