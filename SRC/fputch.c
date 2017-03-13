/*
    module  : fputch.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

/*
fputch  :  S C  ->  S
The character C is written to the current position of stream S.
*/
PRIVATE void do_fputch(void)
{
    int ch;

#ifndef NCHECK
    COMPILE;
    TWOPARAMS("fputch");
    INTEGER("fputch");
#endif
    ch = stk->u.num;
    POP(stk);
#ifndef NCHECK
    FILE("fputch");
#endif
    putc(ch, stk->u.fil);
}
