/*
    module  : jdrawpolygon.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JDRAWPOLYGON_C
#define JDRAWPOLYGON_C

/**
jdrawpolygon  :  obj len x y  ->
Draws an unfilled polygon based on first len elements in x and y.
*/
PRIVATE void do_jdrawpolygon(pEnv env)
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
    x = ListToArray(env->stk->u.lis);
    POP(env->stk);
    y = ListToArray(env->stk->u.lis);
    POP(env->stk);
    len = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_drawpolygon(obj, len, x, y);
}
#endif
