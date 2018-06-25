/*
    module  : fput.c
    version : 1.5
    date    : 06/25/18
*/
#include "runtime.h"

/**
fput  :  S X  ->  S
Writes X to stream S, pops X off stack.
*/
PRIVATE void do_fput(void)
{
    FILE *fp;
    Node temp;

#ifndef NCHECK
    if (optimizing)
	del_history(1);
    COMPILE;
    TWOPARAMS("fput");
    if (stk->next->op != FILE_ || !stk->next->u.fil)
	execerror("file", "fput");
#endif
    temp = *stk;
    POP(stk);
    fp = stk->u.fil;
    writefactor(&temp, fp);
    putc(' ', fp);
}
