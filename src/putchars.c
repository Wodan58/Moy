/*
    module  : putchars.c
    version : 1.7
    date    : 07/10/18
*/
#ifndef PUTCHARS_X
#define PUTCHARS_C

#ifdef RUNTIME
void do_putchars(void)
{
    TRACE;
    printf("%s", do_pop());
}
#else
/**
putchars  :  "abc.."  ->
Writes abc.. (without quotes)
*/
PRIVATE void do_putchars(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    ONEPARAM("putchars");
    STRING("putchars");
    printf("%s", stk->u.str);
    POP(stk);
}
#endif
#endif
