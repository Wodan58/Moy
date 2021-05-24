/*
    module  : jchoicebox3.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JCHOICEBOX3_C
#define JCHOICEBOX3_C

/**
jchoicebox3  :  obj title text button1 button2 button3  ->  event
Shows a choicebox with the specified title, text, and three buttons.
Choiceboxes are modal dialogs, the application is blocked until a button or the
close icon is clicked. The focus is set to the first button. The return value
is 0 if the close icon is clicked, 1 for the first button, 2 for the second and
3 for the third one.
*/
PRIVATE void do_jchoicebox3(pEnv env)
{
    int obj;
    char *title, *text, *button1, *button2, *button3;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    SIXPARAMS(__func__);
    STRING(__func__);
    STRING2(__func__);
    STRING3(__func__);
    STRING4(__func__);
    STRING5(__func__);
    INTEGER6(__func__);
    button3 = env->stk->u.str;
    POP(env->stk);
    button2 = env->stk->u.str;
    POP(env->stk);
    button1 = env->stk->u.str;
    POP(env->stk);
    text = env->stk->u.str;
    POP(env->stk);
    title = env->stk->u.str;
    POP(env->stk);
    obj = env->stk->u.num;
    env->stk->u.num = j_choicebox3(obj, title, text, button1, button2, button3);
}
#endif
