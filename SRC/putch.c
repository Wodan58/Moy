/*
    module  : putch.c
    version : 1.4
    date    : 03/12/17
*/
#include "runtime.h"

/*
putch  :  N  ->
N : numeric, writes character whose ASCII is N.
*/
PRIVATE void do_putch(void)
{
#ifndef NCHECK
    COMPILE;
    ONEPARAM("putch");
    NUMERICTYPE("putch");
#endif
    printf("%c", (int)stk->u.num);
    POP(stk);
}
