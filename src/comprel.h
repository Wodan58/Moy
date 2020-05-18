/*
    module  : comprel.h
    version : 1.11
    date    : 03/28/20
*/
#ifdef CASE_X
#undef CASE_X
#undef CASE_C
#endif

#include "case.c"

PRIVATE void PROCEDURE(void)
{
    double cmp;
    int i, j, error, comp = 0;

#ifndef OLD_RUNTIME
    if (compiling && VALID_1 && VALID_2)
	;
    else
	COMPILE;
#endif
    TWOPARAMS(NAME);
    if (stk->op == SET_) {
	i = stk->next->u.num;
	j = stk->u.num;
	comp = SETCMP;
    } else {
	cmp = Compare(stk->next, stk, &error);
	if (error)
	    BADDATA(NAME);
	else
	    comp = cmp OPR 0;
    }
    stk->next->op = CONSTRUCTOR;
    stk->next->u.num = comp;
    POP(stk);
}

#undef PROCEDURE
#undef NAME
#undef CONSTRUCTOR
#undef OPR
#undef SETCMP
