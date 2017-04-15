/*
    module  : fputch.c
    version : 1.4
    date    : 04/09/17
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
    if (optimizing)
	del_history(1);
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
