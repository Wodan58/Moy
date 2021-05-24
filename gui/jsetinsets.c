/*
    module  : jsetinsets.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETINSETS_C
#define JSETINSETS_C

/**
jsetinsets  :  obj top bottom left right  ->
Sets the insets to the specified values.
*/
PRIVATE void do_jsetinsets(pEnv env)
{
    int obj, top, bottom, left, right;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    FIVEPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    INTEGER3(__func__);
    INTEGER4(__func__);
    INTEGER5(__func__);
    right = env->stk->u.num;
    POP(env->stk);
    left = env->stk->u.num;
    POP(env->stk);
    bottom = env->stk->u.num;
    POP(env->stk);
    top = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_setinsets(obj, top, bottom, left, right);
}
#endif
