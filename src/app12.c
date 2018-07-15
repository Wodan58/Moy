/*
    module  : app12.c
    version : 1.8
    date    : 07/15/18
*/
#ifndef APP12_X
#define APP12_C

#ifndef UNARY2_C
#undef UNARY2_X
#include "unary2.c"
#define UNARY2_X
#endif

#ifdef NEW_RUNTIME
void do_app12(void)
{
    TRACE;
    do_unary2();
    stk[-3] = stk[-2];
    stk[-2] = stk[-1];
    (void)do_pop();
}
#else
/**
app12  :  X Y1 Y2 [P]  ->  R1 R2
Executes P twice, with Y1 and Y2, returns R1 and R2.
*/
PRIVATE void do_app12(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    THREEPARAMS("app12");
    do_unary2();
    stk->next->next = stk->next->next->next;
}
#endif
#endif
