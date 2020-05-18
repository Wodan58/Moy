/*
    module  : x.c
    version : 1.9
    date    : 03/28/20
*/
#ifndef X_C
#define X_C

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
