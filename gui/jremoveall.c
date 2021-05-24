/*
    module  : jremoveall.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JREMOVEALL_C
#define JREMOVEALL_C

/**
jremoveall  :  obj  ->
Removes all items from the component obj.
*/
PRIVATE void do_jremoveall(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    POP(env->stk);
    j_removeall(obj);
}
#endif
