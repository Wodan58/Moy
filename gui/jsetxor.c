/*
    module  : jsetxor.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETXOR_C
#define JSETXOR_C

/**
jsetxor  :  obj bool  ->
Changes painting mode to XOR mode, if bool = J_TRUE. In this mode, drawing the
same object in the same color at the same location twice has no net effect.
*/
PRIVATE void do_jsetxor(pEnv env)
{
    int obj, bool;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    bool = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_setxor(obj, bool);
}
#endif
