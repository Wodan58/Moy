/*
    module  : jsetblockinc.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETBLOCKINC_C
#define JSETBLOCKINC_C

/**
jsetblockinc  :  obj val  ->
Changes the block increment amount for the component to val.
*/
PRIVATE void do_jsetblockinc(pEnv env)
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
    j_setblockinc(obj, val);
}
#endif
