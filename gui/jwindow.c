/*
    module  : jwindow.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JWINDOW_C
#define JWINDOW_C

/**
jwindow  :  obj  ->  event
Creates a new simple window and returns its event number.
*/
PRIVATE void do_jwindow(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    env->stk->u.num = j_window(obj);
}
#endif
