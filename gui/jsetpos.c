/*
    module  : jsetpos.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETPOS_C
#define JSETPOS_C

/**
jsetpos  :  obj xpos ypos  ->
Relocates the component obj to the specified position (xpos, ypos).
*/
PRIVATE void do_jsetpos(pEnv env)
{
    int obj, xpos, ypos;

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
    obj = env->stk->u.num;
    POP(env->stk);
    j_setpos(obj, xpos, ypos);
}
#endif
