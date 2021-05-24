/*
    module  : jprogressbar.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JPROGRESSBAR_C
#define JPROGRESSBAR_C

/**
jprogressbar  :  obj orient  ->  event
Creats a new progress bar with the specified orientation and returns its event
number. Orientation can be J_HORIZONTAL or J_VERTICAL. The progress bar has
predefined values from 0 to 100. This can be changed via jsetmin and jsetmax.
*/
PRIVATE void do_jprogressbar(pEnv env)
{
    int obj, orient;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    orient = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    env->stk->u.num = j_progressbar(obj, orient);
}
#endif
