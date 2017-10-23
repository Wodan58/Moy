/*
    module  : comprel.c
    version : 1.4
    date    : 04/09/17
*/
PRIVATE double Compare(Node *first, Node *second, int *error);

PRIVATE void PROCEDURE(void)
{
    double cmp;
    int i, j, error, comp = 0;

#ifndef NCHECK
    unsigned op, op1;

    if (optimizing) {
	del_history(1);
	op = top_history(&op1);
	chg_history(op == SET_ ? SET_ : BOOLEAN_);
    }
    if (optimizing && VALID(stk) && VALID(stk->next))
	;
    else
	COMPILE;
    TWOPARAMS(NAME);
#endif
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
	} else {
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
