/*
    module  : jseteditable.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETEDITABLE_C
#define JSETEDITABLE_C

/**
jseteditable  :  obj bool  ->
Allows to make the component editable (bool=J_TRUE) or read-only (bool=J_FALSE).
*/
PRIVATE void do_jseteditable(pEnv env)
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
    j_seteditable(obj, bool);
}
#endif
