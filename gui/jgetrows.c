/*
    module  : jgetrows.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JGETROWS_C
#define JGETROWS_C

/**
jgetrows  :  obj  ->  rows
Gets the number of rows in obj.
*/
PRIVATE void do_jgetrows(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    env->stk->u.num = j_getrows(obj);
}
#endif
