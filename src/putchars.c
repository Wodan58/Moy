/*
    module  : putchars.c
    version : 1.4
    date    : 06/25/18
*/
#include "runtime.h"

/**
putchars  :  "abc.."  ->
Writes abc.. (without quotes)
*/
PRIVATE void do_putchars(void)
{
#ifndef NCHECK
    if (optimizing)
	del_history(1);
    COMPILE;
    ONEPARAM("putchars");
    STRING("putchars");
#endif
    printf("%s", stk->u.str);
    POP(stk);
}
