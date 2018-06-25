/*
    module  : x.c
    version : 1.4
    date    : 06/25/18
*/
#include "runtime.h"

/**
x  :  [P] x  ->  ...
Executes P without popping [P]. So, [P] x  ==  [P] P.
*/
PRIVATE void do_x(void)
{
#ifndef NCHECK
    COMPILE;
    ONEPARAM("x");
    ONEQUOTE("x");
#endif
    exeterm(stk->u.lis);
}
