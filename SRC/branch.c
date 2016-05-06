/*
    module  : branch.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
branch  :  B [T] [F]  ->  ...
If B is true, then executes T else executes F.
*/
/* branch.c */
PRIVATE void branch_(void)
{
    int num;
    Node *first, *second;

    THREEPARAMS("branch");
    TWOQUOTES("branch");
    second = stk->u.lis;
    POP(stk);
    first = stk->u.lis;
    POP(stk);
    num = stk->u.num;
    POP(stk);
    exeterm(num ? first : second);
}
