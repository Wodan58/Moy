/*
    module  : comprel.c
    version : 1.2
    date    : 05/06/16
*/
/* comprel.c */
PRIVATE void PROCEDURE(void)
{
    double cmp;
    int i, j, error, comp = 0;

    TWOPARAMS(NAME);
    if (stk->op == SET_) {
	i = stk->next->u.num;
	j = stk->u.num;
	comp = SETCMP;
    } else {
	cmp = Compare(stk->next, stk, &error);
	if (error)
	    BADDATA(NAME);
	else {
	    comp = cmp OPR 0;
	    if (comp < 0)
		comp = -1;
	    else if (comp > 0)
		comp = 1;
	}
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
