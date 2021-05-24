/*
    module  : jsetcolor.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETCOLOR_C
#define JSETCOLOR_C

/**
jsetcolor  :  obj r g b  ->
Sets the foreground color to the (r, g, b) values.
*/
PRIVATE void do_jsetcolor(pEnv env)
{
    int obj, r, g, b;

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
    g = env->stk->u.num;
    POP(env->stk);
    b = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_setcolor(obj, r, g, b);
}
#endif
