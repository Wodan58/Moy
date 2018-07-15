/*
    module  : put.c
    version : 1.8
    date    : 07/15/18
*/
#ifndef PUT_X
#define PUT_C

#ifdef NEW_RUNTIME
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
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM("put");
    writefactor(stk, stdout);
    putchar(' ');
    POP(stk);
}
#endif
#endif
