/*
    module  : dip.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
dip  :  X [P]  ->  ...  X
Saves X, executes P, pushes X back.
*/
/* dip.c */
PRIVATE void dip_(void)
{
    Node *prog, save;

    TWOPARAMS("dip");
    ONEQUOTE("dip");
    prog = stk->u.lis;
    POP(stk);
    save = *stk;
    POP(stk);
    exeterm(prog);
    DUPLICATE(&save);
}
