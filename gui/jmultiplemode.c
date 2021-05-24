/*
    module  : jmultiplemode.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JMULTIPLEMODE_C
#define JMULTIPLEMODE_C

/**
jmultiplemode  :  obj bool  ->
If bool is J_TRUE, selection mode is turned to multiple mode.
*/
PRIVATE void do_jmultiplemode(pEnv env)
{
    int obj, bool;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    bool = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_multiplemode(obj, bool);
}
#endif
