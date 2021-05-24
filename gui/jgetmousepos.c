/*
    module  : jgetmousepos.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JGETMOUSEPOS_C
#define JGETMOUSEPOS_C

/**
jgetmousepos  :  mouselistener  ->  xpos ypos
Returns the current mouse position (xpos, ypos).
*/
PRIVATE void do_jgetmousepos(pEnv env)
{
    int mouselistener, xpos, ypos;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    mouselistener = env->stk->u.num;
    j_getmousepos(mouselistener, &xpos, &ypos);
    env->stk->u.num = xpos;
    PUSH_NUM(INTEGER_, ypos);
}
#endif
