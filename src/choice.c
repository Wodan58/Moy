/*
    module  : choice.c
    version : 1.10
    date    : 03/28/20
*/
#ifndef CHOICE_C
#define CHOICE_C

/**
choice  :  B T F  ->  X
If B is true, then X = T else X = F.
*/
PRIVATE void do_choice(void)
{
#ifndef OLD_RUNTIME
    if (compiling && VALID_1 && VALID_2 && VALID_3)
	;
    else
	COMPILE;
#endif
    THREEPARAMS("choice");
    if (stk->next->next->u.num) {
	stk->next->next->u = stk->next->u;
	stk->next->next->op = stk->next->op;
    } else {
	stk->next->next->u = stk->u;
	stk->next->next->op = stk->op;
    }
    POP(stk);
    POP(stk);
}
#endif
