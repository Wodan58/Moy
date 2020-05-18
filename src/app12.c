/*
    module  : app12.c
    version : 1.9
    date    : 03/28/20
*/
#ifndef APP12_C
#define APP12_C

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
