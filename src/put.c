/*
    module  : put.c
    version : 1.9
    date    : 03/28/20
*/
#ifndef PUT_C
#define PUT_C

/**
put  :  X  ->
Writes X to output, pops X off stack.
*/
PRIVATE void do_put(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM("put");
    writefactor(stk, stdout);
    putchar(' ');
    POP(stk);
}
#endif
