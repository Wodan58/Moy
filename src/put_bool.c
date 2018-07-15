/*
    module  : put_bool.c
    version : 1.3
    date    : 07/15/18
*/
#ifndef PUT_BOOL_X
#define PUT_BOOL_C

#ifdef NEW_RUNTIME
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
