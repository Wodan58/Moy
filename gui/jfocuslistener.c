/*
    module  : 
    version : 1.1
    date    : 04/28/21
*/
#ifndef JFOCUSLISTENER_C
#define JFOCUSLISTENER_C

/**
jfocuslistener  :  obj  ->  event
Adds a new focus listener to component obj and returns its event number.
*/
PRIVATE void do_jfocuslistener(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    env->stk->u.num = j_focuslistener(obj);
}
#endif
