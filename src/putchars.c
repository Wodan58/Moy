/*
    module  : putchars.c
    version : 1.10
    date    : 03/28/20
*/
#ifndef PUTCHARS_C
#define PUTCHARS_C

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
