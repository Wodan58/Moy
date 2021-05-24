/*
    module  : jgetdanger.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JGETDANGER_C
#define JGETDANGER_C

/**
jgetdanger  :  obj  ->  danger
Returns the danger value of component obj.
*/
PRIVATE void do_jgetdanger(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    env->stk->u.num = j_getdanger(obj);
}
#endif
