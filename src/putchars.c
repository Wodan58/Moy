/*
    module  : putchars.c
    version : 1.9
    date    : 04/20/19
*/
#ifndef PUTCHARS_X
#define PUTCHARS_C

#ifdef NEW_RUNTIME
void do_putchars(void)
{
    TRACE;
    printf("%s", (char *)do_pop());
}
#else
/**
putchars  :  "abc.."  ->
Writes abc.. (without quotes)
*/
PRIVATE void do_putchars(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM("putchars");
    STRING("putchars");
    printf("%s", stk->u.str);
    POP(stk);
}
#endif
#endif
