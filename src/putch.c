/*
    module  : putch.c
    version : 1.9
    date    : 07/10/18
*/
#ifndef PUTCH_X
#define PUTCH_C

#ifdef RUNTIME
void do_putch(void)
{
    int ch;

    TRACE;
    ch = do_pop();
    putchar(ch);
}
#else
/**
putch  :  N  ->
N : numeric, writes character whose ASCII is N.
*/
PRIVATE void do_putch(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    ONEPARAM("putch");
    NUMERICTYPE("putch");
    printf("%c", (int)stk->u.num);
    POP(stk);
}
#endif
#endif
