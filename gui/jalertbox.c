/*
    module  : jalertbox.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JALERTBOX_C
#define JALERTBOX_C

/**
jalertbox  :  obj title text button  ->  status
Shows an alertbox with the specified title, text, and button. Alertboxes are
modal dialogs; the application is blocked until the button or the close icon is
clicked. The return value is 0, if the close icon is clicked and 1 if the
button is used.
*/
PRIVATE void do_jalertbox(pEnv env)
{
    int obj;
    char *title, *text, *button;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    FOURPARAMS(__func__);
    STRING(__func__);
    STRING2(__func__);
    STRING3(__func__);
    INTEGER4(__func__);
    button = env->stk->u.str;
    POP(env->stk);
    text = env->stk->u.str;
    POP(env->stk);
    title = env->stk->u.str;
    POP(env->stk);
    obj = env->stk->u.num;
    env->stk->u.num = j_alertbox(obj, title, text, button);
}
#endif
