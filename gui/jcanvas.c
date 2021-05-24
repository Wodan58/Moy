/*
    module  : jcanvas.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JCANVAS_C
#define JCANVAS_C

/**
jcanvas  :  obj width height  ->  event
Creates a new canvas component with the given width and height and returns its
event number. A canvas can be used for general drawing functions. A canvas
generates an event, if its size changes. On error -1 will be returned.
*/
PRIVATE void do_jcanvas(pEnv env)
{
    int obj, width, height;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    THREEPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    INTEGER3(__func__);
    height = env->stk->u.num;
    POP(env->stk);
    width = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    env->stk->u.num = j_canvas(obj, width, height);
}
#endif
