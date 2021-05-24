/*
    module  : 
    version : 1.1
    date    : 04/28/21
*/
#ifndef JGETFONTHEIGHT_C
#define JGETFONTHEIGHT_C

/**
jgetfontheight  :  obj  ->  height
Returns the total pixel height of the actual font of component obj.
*/
PRIVATE void do_jgetfontheight(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    env->stk->u.num = j_getfontheight(obj);
}
#endif
