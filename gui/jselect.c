/*
    module  : jselect.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSELECT_C
#define JSELECT_C

/**
jselect  :  obj item  ->
Makes the given item the selected one for the component obj.
*/
PRIVATE void do_jselect(pEnv env)
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
    j_select(obj, item);
}
#endif
