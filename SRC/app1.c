/*
    module  : app1.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
app1  :  X [P]  ->  R
Executes P, pushes result R on stack with X.
*/
/* app1.c */
PRIVATE void app1_(void)
{
    Node *prog;

    TWOPARAMS("app1");
    ONEQUOTE("app1");
    prog = stk->u.lis;
    POP(stk);
    exeterm(prog);
}
