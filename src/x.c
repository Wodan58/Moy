/*
    module  : x.c
    version : 1.5
    date    : 07/02/18
*/

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
