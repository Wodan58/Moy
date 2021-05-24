/*
    module  : 
    version : 1.1
    date    : 04/28/21
*/
#ifndef JCOMPONENTLISTENER_C
#define JCOMPONENTLISTENER_C

/**
jcomponentlistener  :  obj kind  ->  event
Adds a new componentlistener to component obj, and returns its event number. An
event occurs, if the user action is of kind kind. Possible values for kind:
J_RESIZED: An event occurs when the component has been resized; J_HIDDEN: an
event occurs when the component has been hidden; J_SHOWN: an event occurs when
the component has been shown.
*/
PRIVATE void do_jcomponentlistener(pEnv env)
{
    int obj, kind;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    kind = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    env->stk->u.num = j_componentlistener(obj, kind);
}
#endif
