/*
    module  : cleave.c
    version : 1.5
    date    : 10/04/16
*/
#include "interp.h"

/*
cleave  :  X [P1] [P2]  ->  R1 R2
Executes P1 and P2, each with X on top, producing two results.
*/
/* cleave.c */
PRIVATE void cleave_(void)
{
    Node *prog[2], result[2], *save;

    THREEPARAMS("cleave");
    TWOQUOTES("cleave");
    prog[1] = stk->u.lis;
    POP(stk);
    prog[0] = stk->u.lis;
    POP(stk);
    save = stk;
#ifdef ARITY
    copy_(arity(prog[0]));
#else
    CONDITION;
#endif
    exeterm(prog[0]);
    result[0] = *stk;
    stk = save;
#ifdef ARITY
    copy_(arity(prog[1]));
#endif
    exeterm(prog[1]);
    result[1] = *stk;
    stk = save;
#ifndef ARITY
    RELEASE;
#endif
    POP(stk);
    DUPLICATE(&result[0]);
    DUPLICATE(&result[1]);
}
