/*
    module  : putchars.c
    version : 1.5
    date    : 07/02/18
*/

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
