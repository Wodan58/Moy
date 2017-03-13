/*
    module  : putchars.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
putchars  :  "abc.."  ->
Writes abc.. (without quotes)
*/
PRIVATE void do_putchars(void)
{
#ifndef NCHECK
    COMPILE;
    ONEPARAM("putchars");
    STRING("putchars");
#endif
    printf("%s", stk->u.str);
    POP(stk);
}
