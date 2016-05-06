/*
    module  : times.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
times  :  N [P]  ->  ...
N times executes P.
*/
/* times.c */
PRIVATE void times_(void)
{
    int i, num;
    Node *prog;

    TWOPARAMS("times");
    ONEQUOTE("times");
    INTEGER2("times");
    prog = stk->u.lis;
    POP(stk);
    num = stk->u.num;
    POP(stk);
    for (i = 0; i < num; i++)
	exeterm(prog);
}
