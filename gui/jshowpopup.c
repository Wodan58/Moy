/*
    module  : jshowpopup.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSHOWPOPUP_C
#define JSHOWPOPUP_C

/**
jshowpopup  :  obj xpos ypos  ->
Shows the component at specified position (xpos, ypos).
*/
PRIVATE void do_jshowpopup(pEnv env)
{
    int obj, xpos, ypos;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    THREEPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    INTEGER3(__func__);
    xpos = env->stk->u.num;
    POP(env->stk);
    ypos = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_showpopup(obj, xpos, ypos);
}
#endif
