/*
    module  : comprel.h
    version : 1.6
    date    : 07/02/18
*/
PRIVATE void PROCEDURE(void)
{
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
}

#undef PROCEDURE
#undef NAME
#undef CONSTRUCTOR
#undef OPR
#undef SETCMP
