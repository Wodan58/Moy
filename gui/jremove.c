/*
    module  : jremove.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JREMOVE_C
#define JREMOVE_C

/**
jremove  :  obj item  ->
Removes the item with the index item from the component obj.
*/
PRIVATE void do_jremove(pEnv env)
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
    j_remove(obj, item);
}
#endif
