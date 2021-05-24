/*
    module  : jgetlength.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JGETLENGTH_C
#define JGETLENGTH_C

/**
jgetlength  :  obj  ->  length
Returns the length of component's label or text.
*/
PRIVATE void do_jgetlength(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    env->stk->u.num = j_getlength(obj);
}
#endif
