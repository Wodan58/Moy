/*
    module  : jsetimage.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETIMAGE_C
#define JSETIMAGE_C

/**
jsetimage  :  obj image  ->
Sets the image to be displayed in obj.
*/
PRIVATE void do_jsetimage(pEnv env)
{
    int obj, image;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    image = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_setimage(obj, image);
}
#endif
