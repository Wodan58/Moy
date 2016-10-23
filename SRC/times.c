/*
    module  : times.c
    version : 1.3
    date    : 10/16/16
*/
#include "interp.h"

/*
times  :  N [P]  ->  ...
N times executes P.
*/
/* times.c */
PRIVATE void times_(void)
{
    int num;
    Node *prog;

    TWOPARAMS("times");
    ONEQUOTE("times");
    INTEGER2("times");
    prog = stk->u.lis;
    POP(stk);
    num = stk->u.num;
    POP(stk);
    while (num--)
	exeterm(prog);
}
