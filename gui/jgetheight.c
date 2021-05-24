/*
    module  : jgetheight.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JGETHEIGHT_C
#define JGETHEIGHT_C

/**
jgetheight  :  obj  ->  height
Returns the height of component obj.
*/
PRIVATE void do_jgetheight(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    env->stk->u.num = j_getheight(obj);
}
#endif
