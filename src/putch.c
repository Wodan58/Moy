/*
    module  : putch.c
    version : 1.7
    date    : 07/02/18
*/

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
