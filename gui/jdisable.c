/*
    module  : jdisable.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JDISABLE_C
#define JDISABLE_C

/**
jdisable  :  obj  ->
Disables component obj so that it is unresponsive to user interactions.
*/
PRIVATE void do_jdisable(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    POP(env->stk);
    j_disable(obj);
}
#endif
