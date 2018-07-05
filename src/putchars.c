/*
    module  : putchars.c
    version : 1.6
    date    : 07/05/18
*/
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
