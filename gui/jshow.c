/*
    module  : jshow.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSHOW_C
#define JSHOW_C

/**
jshow  :  obj  ->
Shows the component obj.
*/
PRIVATE void do_jshow(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    POP(env->stk);
    j_show(obj);
}
#endif
