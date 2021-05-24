/*
    module  : jgetselect.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JGETSELECT_C
#define JGETSELECT_C

/**
jgetselect  :  obj  ->  position
Returns the position of the currently selected item.
*/
PRIVATE void do_jgetselect(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    env->stk->u.num = j_getselect(obj);
}
#endif
