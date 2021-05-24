/*
    module  : jmessagebox.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JMESSAGEBOX_C
#define JMESSAGEBOX_C

/**
jmessagebox  :  obj title text  ->  event
Shows a messagebox with the specified title and text and returns its event
number. In the case of an error -1 will be returned. A messagebox generates an
event, if the close icon is clicked.
*/
PRIVATE void do_jmessagebox(pEnv env)
{
    int obj;
    char *title, *text;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    THREEPARAMS(__func__);
    STRING(__func__);
    STRING2(__func__);
    INTEGER3(__func__);
    text = env->stk->u.str;
    POP(env->stk);
    title = env->stk->u.str;
    POP(env->stk);
    obj = env->stk->u.num;
    env->stk->u.num = j_messagebox(obj, title, text);
}
#endif
