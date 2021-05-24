/*
    module  : 
    version : 1.1
    date    : 04/28/21
*/
#ifndef JDRAWSCALEDIMAGE_C
#define JDRAWSCALEDIMAGE_C

/**
jdrawscaledimage  :  obj image sx sy sw sh tx ty tw th  ->
Copy the contents of the rectangular area defined by x, y, width sw and height
sh of the image to position (tx, ty). The area will be scaled to target width
tw and target height th.
*/
PRIVATE void do_jdrawscaledimage(pEnv env)
{
    int obj, image, sx, sy, sw, sh, tx, ty, tw, th;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TENPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    INTEGER3(__func__);
    INTEGER4(__func__);
    INTEGER5(__func__);
    INTEGER6(__func__);
    INTEGER7(__func__);
    INTEGER8(__func__);
    INTEGER9(__func__);
    INTEGER10(__func__);
    th = env->stk->u.num;
    POP(env->stk);
    tw = env->stk->u.num;
    POP(env->stk);
    ty = env->stk->u.num;
    POP(env->stk);
    tx = env->stk->u.num;
    POP(env->stk);
    sh = env->stk->u.num;
    POP(env->stk);
    sw = env->stk->u.num;
    POP(env->stk);
    sy = env->stk->u.num;
    POP(env->stk);
    sx = env->stk->u.num;
    POP(env->stk);
    image = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_drawscaledimage(obj, image, sx, sy, sw, sh, tx, ty, tw, th);
}
#endif
