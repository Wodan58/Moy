/*
    module  : fputch.c
    version : 1.9
    date    : 03/28/20
*/
#ifndef FPUTCH_C
#define FPUTCH_C

/**
fputch  :  S C  ->  S
The character C is written to the current position of stream S.
*/
PRIVATE void do_fputch(void)
{
    int ch;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS("fputch");
    INTEGER("fputch");
    ch = stk->u.num;
    POP(stk);
    FILE("fputch");
    putc(ch, stk->u.fil);
}
#endif
