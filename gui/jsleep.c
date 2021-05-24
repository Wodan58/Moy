/*
    module  : jsleep.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSLEEP_C
#define JSLEEP_C

/**
jsleep  :  msec  ->
Suspends the execution for msec milliseconds.
*/
PRIVATE void do_jsleep(pEnv env)
{
    int msec;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    msec = env->stk->u.num;
    POP(env->stk);
    j_sleep(msec);
}
#endif
