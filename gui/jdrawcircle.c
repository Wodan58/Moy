/*
    module  : jdrawcircle.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JDRAWCIRCLE_C
#define JDRAWCIRCLE_C

/**
jdrawcircle  :  obj x y r  ->
Draws an unfilled circle with center (x, y) and radius x.
*/
PRIVATE void do_jdrawcircle(pEnv env)
{
    int obj, x, y, r;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    FOURPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    INTEGER3(__func__);
    INTEGER4(__func__);
    r = env->stk->u.num;
    POP(env->stk);
    y = env->stk->u.num;
    POP(env->stk);
    x = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_drawcircle(obj, x, y, r);
}
#endif
