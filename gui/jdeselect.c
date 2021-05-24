/*
    module  : jdeselect.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JDESELECT_C
#define JDESELECT_C

/**
jdeselect  :  obj item  ->
Deselects the item at the designated position item, if selected.
*/
PRIVATE void do_jdeselect(pEnv env)
{
    int obj, item;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    item = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_deselect(obj, item);
}
#endif
