/*
    module  : jsetnolayout.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETNOLAYOUT_C
#define JSETNOLAYOUT_C

/**
jsetnolayout  :  obj  ->
Removes the current layout manager from component obj.
*/
PRIVATE void do_jsetnolayout(pEnv env)
{
    int obj, bool;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    POP(env->stk);
    j_setnolayout(obj);
}
#endif
