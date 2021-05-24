/*
    module  : jsetslidesize.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETSLIDESIZE_C
#define JSETSLIDESIZE_C

/**
jsetslidesize  :  obj val  ->
Changes the slide size to val.
*/
PRIVATE void do_jsetslidesize(pEnv env)
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
    j_setslidesize(obj, val);
}
#endif
