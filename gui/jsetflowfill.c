/*
    module  : jsetflowfill.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETFLOWFILL_C
#define JSETFLOWFILL_C

/**
jsetflowfill  :  obj bool  ->
Resizes all contained components to the height (width) of component obj. Needs
a flowlayout manager.
*/
PRIVATE void do_jsetflowfill(pEnv env)
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
    j_setflowfill(obj, bool);
}
#endif
