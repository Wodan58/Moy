/*
    module  : type.h
    version : 1.8
    date    : 03/28/20
*/
PRIVATE void PROCEDURE(void)
{
#ifndef OLD_RUNTIME
    if (compiling && VALID_1)
	;
    else
	COMPILE;
#endif
    ONEPARAM(NAME);
    stk->u.num = stk->op REL TYP;
    stk->op = BOOLEAN_;
}

#undef PROCEDURE
#undef NAME
#undef REL
#undef TYP
