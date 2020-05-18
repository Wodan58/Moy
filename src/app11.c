/*
    module  : app11.c
    version : 1.9
    date    : 03/28/20
*/
#ifndef APP11_C
#define APP11_C

/**
app11  :  X Y [P]  ->  R
Executes P, pushes result R on stack.
*/
PRIVATE void do_app11(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    THREEPARAMS("app11");
    ONEQUOTE("app11");
    do_app1();
    stk->next = stk->next->next;
}
#endif
