/*
    module  : app12.c
    version : 1.7
    date    : 07/10/18
*/
#ifndef APP12_X
#define APP12_C

/**
app12  :  X Y1 Y2 [P]  ->  R1 R2
Executes P twice, with Y1 and Y2, returns R1 and R2.
*/
PRIVATE void do_app12(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    THREEPARAMS("app12");
    do_unary2();
    if (OUTSIDE) {
	stk[-2].op = stk[-1].op;
	stk[-2].u = stk[-1].u;
	stk[-1].op = stk->op;
	stk[-1].u = stk->u;
	stk--;
    } else
	stk->next->next = stk->next->next->next;
}
#endif
