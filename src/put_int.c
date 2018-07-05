/*
    module  : put_int.c
    version : 1.1
    date    : 07/05/18
*/
#ifdef RUNTIME
void do_put_int(void)
{
    TRACE;
    printf("%d ", do_pop());
}
#else
/**
put_int  :  X  ->
Writes X to output, pops X off stack.
*/
PRIVATE void do_put_int(void)
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
