/*
    module  : predsucc.c
    version : 1.2
    date    : 05/06/16
*/
/* predsucc.c */
PRIVATE void PROCEDURE(void)
{
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
