/*
    module  : put.c
    version : 1.6
    date    : 07/05/18
*/
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
