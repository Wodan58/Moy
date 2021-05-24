/*
    module  : 
    version : 1.1
    date    : 04/28/21
*/
#ifndef JGETMOUSEBUTTON_C
#define JGETMOUSEBUTTON_C

/**
jgetmousebutton  :  mouselistener  ->  button
Return the mousebutton that was last used. The return value is: J_LEFT: left
mousebutton; J_CENTER: middle mousebutton; J_RIGHT: right mousebutton.
*/
PRIVATE void do_jgetmousebutton(pEnv env)
{
    int mouselistener;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    mouselistener = env->stk->u.num;
    env->stk->u.num = j_getmousebutton(mouselistener);
}
#endif
