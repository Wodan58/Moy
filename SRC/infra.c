/*
    module  : infra.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
infra  :  L1 [P]  ->  L2
Using list L1 as stack, executes P and returns a new list L2.
The first element of L1 is used as the top of stack,
and after execution of P the top of stack becomes the first element of L2.
*/
/* infra.c */
PRIVATE void infra_(void)
{
    Node *prog, *save;

    TWOPARAMS("infra");
    ONEQUOTE("infra");
    LIST2("infra");
    prog = stk->u.lis;
    POP(stk);
    save = stk->next;
    stk = stk->u.lis;
    inside_condition++;
    exeterm(prog);
    inside_condition--;
    prog = stk;
    stk = save;
    PUSH(LIST_, prog);
}
