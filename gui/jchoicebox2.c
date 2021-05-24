/*
    module  : jchoicebox2.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JCHOICEBOX2_C
#define JCHOICEBOX2_C

/**
jchoicebox2  :  obj title text button1 button2  ->  event
Shows a choicebox with the specified title, text, and two buttons. Choiceboxes
are modal dialogs, the application is blocked until a button or the close icon
is clicked. The focus is set to the first button. The return value is 0 if the
close icon is clicked, 1 for the first button and 2 for the second one.
*/
PRIVATE void do_jchoicebox2(pEnv env)
{
    int obj;
    char *title, *text, *button1, *button2;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    FIVEPARAMS(__func__);
    STRING(__func__);
    STRING2(__func__);
    STRING3(__func__);
    STRING4(__func__);
    INTEGER5(__func__);
    button2 = env->stk->u.str;
    POP(env->stk);
    button1 = env->stk->u.str;
    POP(env->stk);
    text = env->stk->u.str;
    POP(env->stk);
    title = env->stk->u.str;
    POP(env->stk);
    obj = env->stk->u.num;
    env->stk->u.num = j_choicebox2(obj, title, text, button1, button2);
}
#endif
