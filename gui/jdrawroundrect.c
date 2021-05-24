/*
    module  : 
    version : 1.1
    date    : 04/28/21
*/
#ifndef JDRAWROUNDRECT_C
#define JDRAWROUNDRECT_C

/**
jdrawroundrect  :  obj x y width height arcx arcy  ->
Draws an unfilled rectangle from (x, y) of size width x height with rounded
corners; arcx and arcy specify the radius of rectangle corners.
*/
PRIVATE void do_jdrawroundrect(pEnv env)
{
    int obj, x, y, width, height, arcx, arcy;

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
    arcy = env->stk->u.num;
    POP(env->stk);
    arcx = env->stk->u.num;
    POP(env->stk);
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
    j_drawroundrect(obj, x, y, width, height, arcx, arcy);
}
#endif
