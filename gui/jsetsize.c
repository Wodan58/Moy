/*
    module  : jsetsize.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETSIZE_C
#define JSETSIZE_C

/**
jsetsize  :  obj width height  ->
Resizes component obj to the specified width and height.
*/
PRIVATE void do_jsetsize(pEnv env)
{
    int obj, width, height;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    THREEPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    INTEGER3(__func__);
    height = env->stk->u.num;
    POP(env->stk);
    width = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_setsize(obj, width, height);
}
#endif
