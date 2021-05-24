/*
    module  : jsetvgap.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETVGAP_C
#define JSETVGAP_C

/**
jsetvgap  :  obj vgap  ->
Sets the vertical gap between components to hgap pixels.
*/
PRIVATE void do_jsetvgap(pEnv env)
{
    int obj, vgap;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    vgap = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_setvgap(obj, vgap);
}
#endif
