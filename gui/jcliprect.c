/*
    module  : jcliprect.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JCLIPRECT_C
#define JCLIPRECT_C

/**
jcliprect  :  obj x y width height ->
Changes current clipping region to the specified rectangle (x, y, width,
height).
*/
PRIVATE void do_jcliprect(pEnv env)
{
    int obj, x, y, width, height;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    FIVEPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    INTEGER3(__func__);
    INTEGER4(__func__);
    INTEGER5(__func__);
    height = env->stk->u.num;
    POP(env->stk);
    width = env->stk->u.num;
    POP(env->stk);
    y = env->stk->u.num;
    POP(env->stk);
    x = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_cliprect(obj, x, y, width, height);
}
#endif
