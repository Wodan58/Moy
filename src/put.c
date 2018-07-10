/*
    module  : put.c
    version : 1.7
    date    : 07/10/18
*/
#ifndef PUT_X
#define PUT_C

#ifdef RUNTIME
void do_put(void)
{
    TRACE;
    print_node(do_pop());
}
#else
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
#endif
#endif
