/*
    module  : jadditem.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JADDITEM_C
#define JADDITEM_C

/**
jadditem  :  obj str  ->
Adds a new item containing str to component obj.
*/
PRIVATE void do_jadditem(pEnv env)
{
    int obj;
    char *str;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    STRING(__func__);
    INTEGER2(__func__);
    str = env->stk->u.str;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_additem(obj, str);
}
#endif
