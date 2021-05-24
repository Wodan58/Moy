/*
    module  : jdrawimage.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JDRAWIMAGE_C
#define JDRAWIMAGE_C

/**
jdrawimage  :  obj image x y  ->
Copies the image, given by its eventnumber image, to position (x, y).
*/
PRIVATE void do_jdrawimage(pEnv env)
{
    int obj, image, x, y;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    FOURPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    INTEGER3(__func__);
    INTEGER4(__func__);
    y = env->stk->u.num;
    POP(env->stk);
    x = env->stk->u.num;
    POP(env->stk);
    image = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_drawimage(obj, image, x, y);
}
#endif
