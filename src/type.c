/*
    module  : type.c
    version : 1.4
    date    : 04/09/17
*/
PRIVATE void PROCEDURE(void)
{
#ifndef NCHECK
    if (optimizing)
	chg_history(BOOLEAN_);
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
