/*
    module  : unary3.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
unary3  :  X1 X2 X3 [P]  ->  R1 R2 R3
Executes P three times, with Xi, returns Ri (i = 1..3).
*/
/* unary3.c */
PRIVATE void unary3_(void)
{
    Node *prog, *first, *second, *save, *result[3];

    FOURPARAMS("unary3");
    ONEQUOTE("unary3");
    prog = stk->u.lis;
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
    inside_condition--;
    result[2] = stk;
    stk = save;
    DUPLICATE(result[0]);
    DUPLICATE(result[1]);
    DUPLICATE(result[2]);
}
