/*
    module  : jgetselend.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JGETSELEND_C
#define JGETSELEND_C

/**
jgetselend  :  obj  ->  position
Returns the ending position of any selected text.
*/
PRIVATE void do_jgetselend(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    env->stk->u.num = j_getselend(obj);
}
#endif
