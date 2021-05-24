/*
    module  : jdrawpixel.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JDRAWPIXEL_C
#define JDRAWPIXEL_C

/**
jdrawpixel  :  obj x y  ->
Draws a pixel at (x, y).
*/
PRIVATE void do_jdrawpixel(pEnv env)
{
    int obj, x, y;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    THREEPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    INTEGER3(__func__);
    y = env->stk->u.num;
    POP(env->stk);
    x = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_drawpixel(obj, x, y);
}
#endif
