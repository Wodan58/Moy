/*
    module  : jhscrollbar.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JHSCROLLBAR_C
#define JHSCROLLBAR_C

/**
jhscrollbar  :  obj  ->  event
Creates a new horizontal scrollbar and returns its event number.
*/
PRIVATE void do_jhscrollbar(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    env->stk->u.num = j_hscrollbar(obj);
}
#endif
