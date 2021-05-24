/*
    module  : jdrawline.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JDRAWLINE_C
#define JDRAWLINE_C

/**
jdrawline  :  obj x1 y1 x2 y2  ->
Draws a line connecting (x1, y1) and (x2, y2).
*/
PRIVATE void do_jdrawline(pEnv env)
{
    int obj, x1, y1, x2, y2;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    FIVEPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    INTEGER3(__func__);
    INTEGER4(__func__);
    INTEGER5(__func__);
    y2 = env->stk->u.num;
    POP(env->stk);
    x2 = env->stk->u.num;
    POP(env->stk);
    y1 = env->stk->u.num;
    POP(env->stk);
    x1 = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_drawline(obj, x1, y1, x2, y2);
}
#endif
