/*
    module  : jsplitpane.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSPLITPANE_C
#define JSPLITPANE_C

/**
jsplitpane  :  canvas xpos ypos  ->  event
Create a split pane at position (xpos, ypos).
*/
PRIVATE void do_jsplitpane(pEnv env)
{
    int canvas, xpos, ypos;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    THREEPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    INTEGER3(__func__);
    ypos = env->stk->u.num;
    POP(env->stk);
    xpos = env->stk->u.num;
    POP(env->stk);
    canvas = env->stk->u.num;
    env->stk->u.num = j_splitpane(canvas, xpos, ypos);
}
#endif
