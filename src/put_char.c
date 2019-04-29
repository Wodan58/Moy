/*
    module  : %M%
    version : %I%
    date    : %G%
*/
#ifndef PUT_CHAR_X
#define PUT_CHAR_C

#ifdef NEW_RUNTIME
void do_put_char(void)
{
    TRACE;
    printf("'%c ", (int)do_pop());
}
#else
/**
put_char  :  X  ->
Writes X to output, pops X off stack.
*/
PRIVATE void do_put_char(void)
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
