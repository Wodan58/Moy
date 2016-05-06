/*
    module  : ifte.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
ifte  :  [B] [T] [F]  ->  ...
Executes B. If that yields true, then executes T else executes F.
*/
/* ifte.c */
PRIVATE void ifte_(void)
{
    int num;
    Node *second, *first, *test, *save;

    THREEPARAMS("ifte");
    THREEQUOTES("ifte");
    second = stk->u.lis;
    POP(stk);
    first = stk->u.lis;
    POP(stk);
    test = stk->u.lis;
    POP(stk);
    save = stk;
    CONDITION;
    exeterm(test);
    num = stk->u.num;
    RELEASE;
    stk = save;
    exeterm(num ? first : second);
}
