/*
    module  : jsetmax.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETMAX_C
#define JSETMAX_C

/**
jsetmax  :  obj val  ->
Changes the maximum value for the component to val.
*/
PRIVATE void do_jsetmax(pEnv env)
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
    j_setmax(obj, val);
}
#endif
