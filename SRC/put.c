/*
    module  : put.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
put  :  X  ->
Writes X to output, pops X off stack.
*/
PRIVATE void do_put(void)
{
#ifndef NCHECK
    COMPILE;
    ONEPARAM("put");
#endif
    writefactor(stk, stdout);
    putchar(' ');
    POP(stk);
}
