/*
    module  : jpanel.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JPANEL_C
#define JPANEL_C

/**
jpanel  :  obj  ->  event
Creates a new panel component and returns its event number.
*/
PRIVATE void do_jpanel(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    env->stk->u.num = j_panel(obj);
}
#endif
