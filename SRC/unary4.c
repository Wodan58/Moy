/*
    module  : unary4.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
unary4  :  X1 X2 X3 X4 [P]  ->  R1 R2 R3 R4
Executes P four times, with Xi, returns Ri (i = 1..4).
*/
/* unary4.c */
PRIVATE void unary4_(void)
{
    Node *prog, *first, *second, *third, *save, *result[4];

    FIVEPARAMS("unary4");
    ONEQUOTE("unary4");
    prog = stk->u.lis;
    POP(stk);
    third = stk;
    POP(stk);
    second = stk;
    POP(stk);
    first = stk;
    POP(stk);
    save = stk->next;
    inside_condition++;
    exeterm(prog);
    result[0] = stk;
    stk = save;
    DUPLICATE(first);
    exeterm(prog);
    result[1] = stk;
    stk = save;
    DUPLICATE(second);
    exeterm(prog);
    result[2] = stk;
    stk = save;
    DUPLICATE(third);
    exeterm(prog);
    inside_condition--;
    result[3] = stk;
    stk = save;
    DUPLICATE(result[0]);
    DUPLICATE(result[1]);
    DUPLICATE(result[2]);
    DUPLICATE(result[3]);
}
