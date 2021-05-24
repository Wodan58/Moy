/*
    module  : jreleaseall.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JRELEASEALL_C
#define JRELEASEALL_C

/**
jreleaseall  :  obj  ->
Releases all components from component obj.
*/
PRIVATE void do_jreleaseall(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    POP(env->stk);
    j_releaseall(obj);
}
#endif
