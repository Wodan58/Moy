/*
    module  : jdrawstring.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JDRAWSTRING_C
#define JDRAWSTRING_C

/**
jdrawstring  :  obj x y str  ->
Draws text on screen at position (x, y).
*/
PRIVATE void do_jdrawstring(pEnv env)
{
    char *str;
    int obj, x, y;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    FOURPARAMS(__func__);
    STRING(__func__);
    INTEGER2(__func__);
    INTEGER3(__func__);
    INTEGER4(__func__);
    str = env->stk->u.str;
    POP(env->stk);
    y = env->stk->u.num;
    POP(env->stk);
    x = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_drawstring(obj, x, y, str);
}
#endif
