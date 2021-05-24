/*
    module  : jhasfocus.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JHASFOCUS_C
#define JHASFOCUS_C

/**
jhasfocus  :  obj  ->  status
Returns J_TRUE if the component has the focus, J_FALSE otherwise.
*/
PRIVATE void do_jhasfocus(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    env->stk->u.num = j_hasfocus(obj);
}
#endif
