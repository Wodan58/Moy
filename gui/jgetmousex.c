/*
    module  : jgetmousex.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JGETMOUSEX_C
#define JGETMOUSEX_C

/**
jgetmousex  :  mouselistener  ->  xpos
Returns the current horizontal position of the mouse in its parent's coordinate
space.
*/
PRIVATE void do_jgetmousex(pEnv env)
{
    int mouselistener;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    mouselistener = env->stk->u.num;
    env->stk->u.num = j_getmousex(mouselistener);
}
#endif
