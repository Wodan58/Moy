/*
    module  : putchars.c
    version : 1.11
    date    : 03/15/21
*/
#ifndef PUTCHARS_C
#define PUTCHARS_C

/**
putchars  :  "abc.."  ->
Writes abc.. (without quotes)
*/
PRIVATE void do_putchars(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM("putchars");
    STRING("putchars");
    printf("%s", env->stk->u.str);
    POP(env->stk);
}
#endif
