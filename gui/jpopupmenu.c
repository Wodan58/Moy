/*
    module  : jpopupmenu.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JPOPUPMENU_C
#define JPOPUPMENU_C

/**
jpopupmenu  :  obj label  ->  event
Creates a new popupmenu with the specified label and returns its event number.
*/
PRIVATE void do_jpopupmenu(pEnv env)
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
    env->stk->u.num = j_popupmenu(obj, label);
}
#endif
