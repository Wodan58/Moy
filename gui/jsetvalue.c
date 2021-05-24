/*
    module  : jsetvalue.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETVALUE_C
#define JSETVALUE_C

/**
jsetvalue  :  obj val  ->
Changes the current value of the component to val.
*/
PRIVATE void do_jsetvalue(pEnv env)
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
    j_setvalue(obj, val);
}
#endif
