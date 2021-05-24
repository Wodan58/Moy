/*
    module  : jscrollpane.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSCROLLPANE_C
#define JSCROLLPANE_C

/**
jscrollpane  :  obj  ->  event
Creates a new scrollpane component and returns its event number.
*/
PRIVATE void do_jscrollpane(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    env->stk->u.num = j_scrollpane(obj);
}
#endif
