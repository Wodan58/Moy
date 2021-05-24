/*
    module  : jfillcircle.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JFILLCIRCLE_C
#define JFILLCIRCLE_C

/**
jfillcircle  :  obj x y r  ->
Draws a filled circle with center (x, y) and radius r.
*/
PRIVATE void do_jfillcircle(pEnv env)
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
    j_fillcircle(obj, x, y, r);
}
#endif
