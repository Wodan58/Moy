/*
    module  : i.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
i  :  [P]  ->  ...
Executes P. So, [P] i  ==  P.
*/
/* i.c */
PRIVATE void i_(void)
{
    Node *prog;

    ONEPARAM("i");
    ONEQUOTE("i");
    prog = stk->u.lis;
    POP(stk);
    exeterm(prog);
}
