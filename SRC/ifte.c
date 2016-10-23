/*
    module  : ifte.c
    version : 1.7
    date    : 10/16/16
*/
#include "interp.h"

/*
ifte  :  [B] [T] [F]  ->  ...
Executes B. If that yields true, then executes T else executes F.
*/
/* ifte.c */
PRIVATE void ifte_(void)
{
    Node *third, *second, *first, *save;

    THREEPARAMS("ifte");
    THREEQUOTES("ifte");
    third = stk->u.lis;
    POP(stk);
    second = stk->u.lis;
    POP(stk);
    first = stk->u.lis;
    POP(stk);
    save = stk;
#ifdef ARITY
    copy_(arity(first));
#else
    CONDITION;
#endif
    exeterm(first);
    first = stk->u.num ? second : third;
    stk = save;
#ifndef ARITY
    RELEASE;
#endif
    exeterm(first);
}
