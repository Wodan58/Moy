/*
    module  : x.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
x  :  [P] x  ->  ...
Executes P without popping [P]. So, [P] x  ==  [P] P.
*/
/* x.c */
PRIVATE void x_(void)
{
    ONEPARAM("x");
    ONEQUOTE("x");
    exeterm(stk->u.lis);
}
