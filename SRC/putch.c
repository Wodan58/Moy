/*
    module  : putch.c
    version : 1.5
    date    : 04/09/17
*/
#include "runtime.h"

/*
putch  :  N  ->
N : numeric, writes character whose ASCII is N.
*/
PRIVATE void do_putch(void)
{
#ifndef NCHECK
    if (optimizing)
	del_history(1);
    COMPILE;
    ONEPARAM("putch");
    NUMERICTYPE("putch");
#endif
    printf("%c", (int)stk->u.num);
    POP(stk);
}
