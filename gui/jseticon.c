/*
    module  : jseticon.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETICON_C
#define JSETICON_C

/**
jseticon  :  frame icon  ->
Sets the image icon to display when the frame is iconized. Not all platforms
support the concept of iconizing a window.
*/
PRIVATE void do_jseticon(pEnv env)
{
    int frame, icon;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    icon = env->stk->u.num;
    POP(env->stk);
    frame = env->stk->u.num;
    POP(env->stk);
    j_seticon(frame, icon);
}
#endif
