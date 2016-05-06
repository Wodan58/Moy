/*
    module  : cleave.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
cleave  :  X [P1] [P2]  ->  R1 R2
Executes P1 and P2, each with X on top, producing two results.
*/
/* cleave.c */
PRIVATE void cleave_(void)
{
    Node *prog[2], *result[2], *save;

    THREEPARAMS("cleave");
    TWOQUOTES("cleave");
    prog[1] = stk->u.lis;
    POP(stk);
    prog[0] = stk->u.lis;
    POP(stk);
    save = stk;
    inside_condition++;
    exeterm(prog[0]);
    result[0] = stk;
    stk = save;
    exeterm(prog[1]);
    inside_condition--;
    result[1] = stk;
    stk = save;
    POP(stk);
    DUPLICATE(result[0]);
    DUPLICATE(result[1]);
}
