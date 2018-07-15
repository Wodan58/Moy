/*
    module  : x.c
    version : 1.8
    date    : 07/15/18
*/
#ifndef X_X
#define X_C

#ifdef NEW_RUNTIME
void do_x(void)
{
    TRACE;
    execute((code_t *)stk[-1]);
}
#else
/**
x  :  [P] x  ->  ...
Executes P without popping [P]. So, [P] x  ==  [P] P.
*/
PRIVATE void do_x(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM("x");
    ONEQUOTE("x");
    exeterm(stk->u.lis);
}
#endif
#endif
