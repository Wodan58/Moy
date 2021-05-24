/*
    module  : jdialog.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JDIALOG_C
#define JDIALOG_C

/**
jdialog  :  obj label  ->  event
Creates a new dialog window with the specified label and returns its event
number.
*/
PRIVATE void do_jdialog(pEnv env)
{
    int obj;
    char *label;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    STRING(__func__);
    INTEGER2(__func__);
    label = env->stk->u.str;
    POP(env->stk);
    obj = env->stk->u.num;
    env->stk->u.num = j_dialog(obj, label);
}
#endif
