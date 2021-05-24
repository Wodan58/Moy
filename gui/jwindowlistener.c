/*
    module  : 
    version : 1.1
    date    : 04/28/21
*/
#ifndef JWINDOWLISTENER_C
#define JWINDOWLISTENER_C

/**
jwindowlistener  :  window kind  ->  event
Adds a new windowlistener to component obj, and returns its event number. An
event occurs, if the user action is of kind kind. Possible values for kind: An
event occurs when the component J_ACTIVATED is activated; J_DEACTIVATED is
deactivated; J_OPENED has been opened; J_CLOSED closed; J_ICONIFIED iconified;
J_DEICONIFIED deiconified; J_CLOSING when the close icon has been clicked.
*/
PRIVATE void do_jwindowlistener(pEnv env)
{
    int window, kind;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    kind = env->stk->u.num;
    POP(env->stk);
    window = env->stk->u.num;
    env->stk->u.num = j_windowlistener(window, kind);
}
#endif
