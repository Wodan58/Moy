/*
    module  : fputch.c
    version : 1.6
    date    : 07/02/18
*/

/**
fputch  :  S C  ->  S
The character C is written to the current position of stream S.
*/
PRIVATE void do_fputch(void)
{
    int ch;

#ifndef NCHECK
    COMPILE;
#endif
    TWOPARAMS("fputch");
    INTEGER("fputch");
    ch = stk->u.num;
    POP(stk);
    FILE("fputch");
    putc(ch, stk->u.fil);
}
