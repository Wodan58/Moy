/*
    module  : jgetlayoutid.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JGETLAYOUTID_C
#define JGETLAYOUTID_C

/**
jgetlayoutid  :  obj  ->  event
Returns the event number of the layoutmanager for container obj.
*/
PRIVATE void do_jgetlayoutid(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    env->stk->u.num = j_getlayoutid(obj);
}
#endif
