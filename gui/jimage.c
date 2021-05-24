/*
    module  : jimage.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JIMAGE_C
#define JIMAGE_C

/**
jimage  :  width height  ->  event
Creates a new (memory) image component with the given width and height and
returns its event number. On error -1 will be returned.
*/
PRIVATE void do_jimage(pEnv env)
{
    int width, height;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    height = env->stk->u.num;
    POP(env->stk);
    width = env->stk->u.num;
    env->stk->u.num = j_image(width, height);
}
#endif
