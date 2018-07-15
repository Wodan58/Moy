/*
    module  : fputch.c
    version : 1.8
    date    : 07/15/18
*/
#ifndef FPUTCH_X
#define FPUTCH_C

#ifdef NEW_RUNTIME
void do_fputch(void)
{
    int ch;

    TRACE;
    ch = do_pop();
    putc(ch, (FILE *)stk[-1]);
}
#else
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
#endif
