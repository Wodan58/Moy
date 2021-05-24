/*
    module  : jremoveitem.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JREMOVEITEM_C
#define JREMOVEITEM_C

/**
jremoveitem  :  obj item  ->
Removes the first occurrence of item from the component.
*/
PRIVATE void do_jremoveitem(pEnv env)
{
    int obj;
    char *item;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    STRING(__func__);
    INTEGER2(__func__);
    item = env->stk->u.str;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_removeitem(obj, item);
}
#endif
