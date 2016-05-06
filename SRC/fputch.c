/*
    module  : fputch.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
fputch  :  S C  ->  S
The character C is written to the current position of stream S.
*/
/* fputch.c */
PRIVATE void fputch_(void)
{
    int ch;

    TWOPARAMS("fputch");
    INTEGER("fputch");
    ch = stk->u.num;
    POP(stk);
    FILE("fputch");
    putc(ch, stk->u.fil);
}
