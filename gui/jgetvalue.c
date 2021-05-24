/*
    module  : jgetvalue.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JGETVALUE_C
#define JGETVALUE_C

/**
jgetvalue  :  obj  ->  value
Returns the current setting of the scrollbar.
*/
PRIVATE void do_jgetvalue(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    env->stk->u.num = j_getvalue(obj);
}
#endif
