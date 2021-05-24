/*
    module  : jsetmin.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETMIN_C
#define JSETMIN_C

/**
jsetmin  :  obj val  ->
Changes the minimum value for the component to val.
*/
PRIVATE void do_jsetmin(pEnv env)
{
    int obj, val;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    val = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_setmin(obj, val);
}
#endif
