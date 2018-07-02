/*
    module  : put.c
    version : 1.5
    date    : 07/02/18
*/

/**
put  :  X  ->
Writes X to output, pops X off stack.
*/
PRIVATE void do_put(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    ONEPARAM("put");
    writefactor(stk, stdout);
    putchar(' ');
    POP(stk);
}
