/*
    module  : jsetunitinc.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETUNITINC_C
#define JSETUNITINC_C

/**
jsetunitinc  :  obj val  ->
Changed the unit increment amount for the component to val.
*/
PRIVATE void do_jsetunitinc(pEnv env)
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
    j_setunitinc(obj, val);
}
#endif
