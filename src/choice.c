/*
    module  : choice.c
    version : 1.8
    date    : 07/10/18
*/
#ifndef CHOICE_X
#define CHOICE_C

/**
choice  :  B T F  ->  X
If B is true, then X = T else X = F.
*/
PRIVATE void do_choice(void)
{
#ifndef NCHECK
    if (compiling && VALID_1 && VALID_2 && VALID_3)
	;
    else
	COMPILE;
#endif
    THREEPARAMS("choice");
    if (OUTSIDE) {
	if (stk->next->next->u.num) {
	    stk->next->next->u = stk->next->u;
	    stk->next->next->op = stk->next->op;
	} else {
	    stk->next->next->u = stk->u;
	    stk->next->next->op = stk->op;
	}
	POP(stk);
	POP(stk);
    } else if (stk->next->next->u.num)
	GTERNARY(stk->next->op, stk->next->u.ptr);
    else
	GTERNARY(stk->op, stk->u.ptr);
}
#endif
