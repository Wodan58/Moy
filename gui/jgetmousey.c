/*
    module  : jgetmousey.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JGETMOUSEY_C
#define JGETMOUSEY_C

/**
jgetmousey  :  mouselistener  ->  ypos
Returns the current vertical position of the mouse in its parent's coordinate
space.
*/
PRIVATE void do_jgetmousey(pEnv env)
{
    int mouselistener;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    mouselistener = env->stk->u.num;
    env->stk->u.num = j_getmousey(mouselistener);
}
#endif
