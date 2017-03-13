/*
    module  : type.c
    version : 1.3
    date    : 03/12/17
*/
PRIVATE void PROCEDURE(void)
{
#ifndef NCHECK
    if (optimizing && VALID(stk))
	;
    else
	COMPILE;
    ONEPARAM(NAME);
#endif
    if (OUTSIDE) {
	stk->u.num = stk->op REL TYP;
	stk->op = BOOLEAN_;
    } else
	UNARY(BOOLEAN_NEWNODE, stk->op REL TYP);
}

#undef PROCEDURE
#undef NAME
#undef REL
#undef TYP
