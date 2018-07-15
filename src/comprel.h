/*
    module  : comprel.h
    version : 1.9
    date    : 07/15/18
*/
#ifndef NEW_RUNTIME
#ifndef CASE_C
#undef CASE_X
#include "case.c"
#define CASE_X
#endif
#endif

PRIVATE void PROCEDURE(void)
{
#ifdef NEW_RUNTIME
    TRACE;
    if (IS_STRING(stk[-2]))
	stk[-2] = strcmp((char *)stk[-2], (char *)stk[-1]) OPR 0;
    else
	stk[-2] = stk[-2] OPR stk[-1];
    (void)do_pop();
#else
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
    if (OUTSIDE) {
	stk->next->op = CONSTRUCTOR;
	stk->next->u.num = comp;
	POP(stk);
    } else {
	POP(stk);
	POP(stk);
	PUSH(CONSTRUCTOR, (long_t)comp);
    }
#endif
}

#undef PROCEDURE
#undef NAME
#undef CONSTRUCTOR
#undef OPR
#undef SETCMP
