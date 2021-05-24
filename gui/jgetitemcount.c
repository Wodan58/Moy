/*
    module  : jgetitemcount.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JGETITEMCOUNT_C
#define JGETITEMCOUNT_C

/**
jgetitemcount  :  obj  ->  count
Returns the number of items of component obj.
*/
PRIVATE void do_jgetitemcount(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    env->stk->u.num = j_getitemcount(obj);
}
#endif
