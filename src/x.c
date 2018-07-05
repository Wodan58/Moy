/*
    module  : x.c
    version : 1.6
    date    : 07/05/18
*/
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
