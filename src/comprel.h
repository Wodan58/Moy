/*
    module  : comprel.h
    version : 1.7
    date    : 07/05/18
*/
PRIVATE void PROCEDURE(void)
{
#ifdef RUNTIME
    TRACE;
    if (stk[-2] > start_of_data && stk[-2] < start_of_heap)
	stk[-2] = strcmp((char *)stk[-2], (char *)stk[-1]) OPR 0;
    else
	stk[-2] = stk[-2] OPR stk[-1];
    stk--;
#else
    double cmp;
    int i, j, error, comp = 0;

#ifndef NCHECK
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
	if (error) {
#ifndef NCHECK
	    BADDATA(NAME);
#endif
	} else
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
