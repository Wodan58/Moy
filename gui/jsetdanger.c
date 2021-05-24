/*
    module  : jsetdanger.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETDANGER_C
#define JSETDANGER_C

/**
jsetdanger  :  obj val  ->
Changes the danger value of component obj to val.
*/
PRIVATE void do_jsetdanger(pEnv env)
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
    j_setdanger(obj, val);
}
#endif
