/*
    module  : jcheckbox.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JCHECKBOX_C
#define JCHECKBOX_C

/**
jcheckbox  :  obj label  ->  event
Creates a new checkbox component with the specified label and returns its event
number.
*/
PRIVATE void do_jcheckbox(pEnv env)
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
    env->stk->u.num = j_checkbox(obj, label);
}
#endif
