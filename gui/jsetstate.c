/*
    module  : jsetstate.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETSTATE_C
#define JSETSTATE_C

/**
jsetstate  :  obj bool  ->
The component becomes selected, if bool is J_TRUE.
*/
PRIVATE void do_jsetstate(pEnv env)
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
    j_setstate(obj, bool);
}
#endif
