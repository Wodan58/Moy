/*
    module  : put.c
    version : 1.3
    date    : 04/09/17
*/
#include "runtime.h"

/*
put  :  X  ->
Writes X to output, pops X off stack.
*/
PRIVATE void do_put(void)
{
#ifndef NCHECK
    if (optimizing)
	del_history(1);
    COMPILE;
    ONEPARAM("put");
#endif
    writefactor(stk, stdout);
    putchar(' ');
    POP(stk);
}
