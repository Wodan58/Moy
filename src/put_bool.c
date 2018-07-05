/*
    module  : put_bool.c
    version : 1.1
    date    : 07/05/18
*/
#ifdef RUNTIME
void do_put_bool(void)
{
    TRACE;
    printf(do_pop() ? "true " : "false ");
}
#else
/**
put_bool  :  X  ->
Writes X to output, pops X off stack.
*/
PRIVATE void do_put_bool(void)
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
