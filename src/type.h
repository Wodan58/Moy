/*
    module  : type.h
    version : 1.5
    date    : 07/02/18
*/
PRIVATE void PROCEDURE(void)
{
#ifndef NCHECK
    if (compiling && VALID_1)
	;
    else
	COMPILE;
#endif
    ONEPARAM(NAME);
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
