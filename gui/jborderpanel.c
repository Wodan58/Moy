/*
    module  : jborderpanel.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JBORDERPANEL_C
#define JBORDERPANEL_C

/**
jborderpanel  :  obj type  ->  event
Creates a new borderpanel component with the style type and returns its event
number.
*/
PRIVATE void do_jborderpanel(pEnv env)
{
    int obj, type;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    type = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    env->stk->u.num = j_borderpanel(obj, type);
}
#endif
