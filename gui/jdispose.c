/*
    module  : jdispose.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JDISPOSE_C
#define JDISPOSE_C

/**
jdispose  :  obj  ->
Releases the resources of the component obj.
*/
PRIVATE void do_jdispose(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    POP(env->stk);
    j_dispose(obj);
}
#endif
