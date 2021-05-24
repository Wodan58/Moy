/*
    module  : jfillpolygon.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JFILLPOLYGON_C
#define JFILLPOLYGON_C

/**
jfillpolygon  :  obj len x y  ->
Draws a filled polygon based on first len elements in x and y.
*/
PRIVATE void do_jfillpolygon(pEnv env)
{
    int obj, len, *x, *y;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    FOURPARAMS(__func__);
    LIST(__func__);
    LIST2(__func__);
    INTEGER3(__func__);
    INTEGER4(__func__);
    y = ListToArray(env->stk->u.lis);
    POP(env->stk);
    x = ListToArray(env->stk->u.lis);
    POP(env->stk);
    len = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_fillpolygon(obj, len, x, y);
}
#endif
