/*
    module  : put_bool.c
    version : 1.2
    date    : 07/10/18
*/
#ifndef PUT_BOOL_X
#define PUT_BOOL_C

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
#endif
