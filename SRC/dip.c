/*
    module  : dip.c
    version : 1.3
    date    : 10/04/16
*/
#include "interp.h"

/*
dip  :  X [P]  ->  ...  X
Saves X, executes P, pushes X back.
*/
/* dip.c */
PRIVATE void dip_(void)
{
    Node *prog, temp;

    TWOPARAMS("dip");
    ONEQUOTE("dip");
    prog = stk->u.lis;
    POP(stk);
    temp = *stk;
    POP(stk);
    exeterm(prog);
    DUPLICATE(&temp);
}
