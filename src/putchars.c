/*
    module  : putchars.c
    version : 1.12
    date    : 06/20/22
*/
#ifndef PUTCHARS_C
#define PUTCHARS_C

/**
putchars  :  "abc.."  ->
Writes abc.. (without quotes)
*/
PRIVATE void do_putchars(pEnv env)
{
    COMPILE;
    ONEPARAM("putchars");
    STRING("putchars");
    printf("%s", env->stk->u.str);
    POP(env->stk);
}
#endif
