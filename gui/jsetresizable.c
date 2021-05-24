/*
    module  : jsetresizable.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETRESIZABLE_C
#define JSETRESIZABLE_C

/**
jsetresizable  :  obj resizable  ->
The component cannot be resized, if resizable is J_FALSE.
*/
PRIVATE void do_jsetresizable(pEnv env)
{
    int obj, resizable;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    resizable = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_setresizable(obj, resizable);
}
#endif
