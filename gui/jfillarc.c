/*
    module  : jfillarc.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JFILLARC_C
#define JFILLARC_C

/**
jfillarc  :  obj x y rx ry arc1 arc2  ->
Draws an filled arc from angle arc11 to angle arc2 with the center (x, y) and
the horizontal radius rx and the vertical radius ry.
*/
PRIVATE void do_jfillarc(pEnv env)
{
    int obj, x, y, rx, ry, arc1, arc2;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    SEVENPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    INTEGER3(__func__);
    INTEGER4(__func__);
    INTEGER5(__func__);
    INTEGER6(__func__);
    INTEGER7(__func__);
    arc2 = env->stk->u.num;
    POP(env->stk);
    arc1 = env->stk->u.num;
    POP(env->stk);
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
    j_fillarc(obj, x, y, rx, ry, arc1, arc2);
}
#endif
