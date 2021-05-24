/*
    module  : jmenuitem.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JMENUITEM_C
#define JMENUITEM_C

/**
jmenuitem  :  obj label  ->  event
Creates a new menuitem with the specified label and returns its event number.
*/
PRIVATE void do_jmenuitem(pEnv env)
{
    int obj;
    char *label;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    STRING(__func__);
    INTEGER2(__func__);
    label = env->stk->u.str;
    POP(env->stk);
    obj = env->stk->u.num;
    env->stk->u.num = j_menuitem(obj, label);
}
#endif
