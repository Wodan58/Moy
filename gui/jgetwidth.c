/*
    module  : jgetwidth.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JGETWIDTH_C
#define JGETWIDTH_C

/**
jgetwidth  :  obj  ->  width
Returns the width of component obj.
*/
PRIVATE void do_jgetwidth(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    env->stk->u.num = j_getwidth(obj);
}
#endif
