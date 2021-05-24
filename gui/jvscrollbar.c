/*
    module  : jvscrollbar.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JVSCROLLBAR_C
#define JVSCROLLBAR_C

/**
jvscrollbar  :  obj  ->  event
Creates a new vertical scrollbar and returns its event number.
*/
PRIVATE void do_jvscrollbar(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    env->stk->u.num = j_vscrollbar(obj);
}
#endif
