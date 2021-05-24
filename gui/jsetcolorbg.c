/*
    module  : jsetcolorbg.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETCOLORBG_C
#define JSETCOLORBG_C

/**
jsetcolorbg  :  obj r g b  ->
Sets the background color to the (r, g, b) values.
*/
PRIVATE void do_jsetcolorbg(pEnv env)
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
    b = env->stk->u.num;
    POP(env->stk);
    g = env->stk->u.num;
    POP(env->stk);
    r = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_setcolorbg(obj, r, g, b);
}
#endif
