/*
    module  : jdrawoval.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JDRAWOVAL_C
#define JDRAWOVAL_C

/**
jdrawoval  :  obj x y rx ry  ->
Draws an unfilled oval with the center (x, y) and the horizontal radius rx and
the vertical radius ry.
*/
PRIVATE void do_jdrawoval(pEnv env)
{
    int obj, x, y, rx, ry;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    FIVEPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    INTEGER3(__func__);
    INTEGER4(__func__);
    INTEGER5(__func__);
    ry = env->stk->u.num;
    POP(env->stk);
    rx = env->stk->u.num;
    POP(env->stk);
    y = env->stk->u.num;
    POP(env->stk);
    x = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_drawoval(obj, x, y, rx, ry);
}
#endif
