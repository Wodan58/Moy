/*
    module  : put_int.c
    version : 1.4
    date    : 04/20/19
*/
#ifndef PUT_INT_X
#define PUT_INT_C

#ifdef NEW_RUNTIME
void do_put_int(void)
{
    TRACE;
    printf("%d ", (int)do_pop());
}
#else
/**
put_int  :  X  ->
Writes X to output, pops X off stack.
*/
PRIVATE void do_put_int(void)
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
