/*
    module  : jrelease.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JRELEASE_C
#define JRELEASE_C

/**
jrelease  :  obj  ->
Releases component obj from its parent component (container).
*/
PRIVATE void do_jrelease(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    POP(env->stk);
    j_release(obj);
}
#endif
