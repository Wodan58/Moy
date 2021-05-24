/*
    module  : 
    version : 1.1
    date    : 04/28/21
*/
#ifndef JGETSCALEDIMAGE_C
#define JGETSCALEDIMAGE_C

/**
jgetscaledimage  :  obj x y sw sh tw th  ->  status
Copy the contents of the rectangular area defined by x, y, width sw, and height
sh into an image and return its event number. The image will be scaled to
target width tw and target height th.
*/
PRIVATE void do_jgetscaledimage(pEnv env)
{
    int obj, x, y, sw, sh, tw, th;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    SEVENPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    INTEGER3(__func__);
    INTEGER4(__func__);
    INTEGER5(__func__);
    INTEGER6(__func__);
    INTEGER7(__func__);
    th = env->stk->u.num;
    POP(env->stk);
    tw = env->stk->u.num;
    POP(env->stk);
    sh = env->stk->u.num;
    POP(env->stk);
    sw = env->stk->u.num;
    POP(env->stk);
    y = env->stk->u.num;
    POP(env->stk);
    x = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    env->stk->u.num = j_getscaledimage(obj, x, y, sw, sh, tw, th);
}
#endif
