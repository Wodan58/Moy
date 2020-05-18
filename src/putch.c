/*
    module  : putch.c
    version : 1.11
    date    : 03/28/20
*/
#ifndef PUTCH_C
#define PUTCH_C

/**
putch  :  N  ->
N : numeric, writes character whose ASCII is N.
*/
PRIVATE void do_putch(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM("putch");
    NUMERICTYPE("putch");
    printf("%c", (int)stk->u.num);
    POP(stk);
}
#endif
