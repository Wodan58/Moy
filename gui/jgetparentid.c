/*
    module  : jgetparentid.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JGETPARENTID_C
#define JGETPARENTID_C

/**
jgetparentid  :  obj  ->  event
Returns the parent event number of component obj. If obj is a frame -1 will be
returned.
*/
PRIVATE void do_jgetparentid(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    env->stk->u.num = j_getparentid(obj);
}
#endif
