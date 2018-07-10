/*
    module  : x.c
    version : 1.7
    date    : 07/10/18
*/
#ifndef X_X
#define X_C

#ifdef RUNTIME
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
#ifndef NCHECK
    COMPILE;
#endif
    ONEPARAM("x");
    ONEQUOTE("x");
    exeterm(stk->u.lis);
}
#endif
#endif
