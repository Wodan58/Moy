/*
    module  : unary2.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
unary2  :  X1 X2 [P]  ->  R1 R2
Executes P twice, with X1 and X2 on top of the stack.
Returns the two values R1 and R2.
*/
/* unary2.c */
PRIVATE void unary2_(void)
{
    Node *prog, *parm, *save, *result[2];

    THREEPARAMS("unary2");
    ONEQUOTE("unary2");
    prog = stk->u.lis;
    POP(stk);
    parm = stk;
    POP(stk);
    save = stk->next;
    inside_condition++;
    exeterm(prog);
    result[0] = stk;
    stk = save;
    DUPLICATE(parm);
    exeterm(prog);
    inside_condition--;
    result[1] = stk;
    stk = save;
    DUPLICATE(result[0]);
    DUPLICATE(result[1]);
}
