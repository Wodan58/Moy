/*
    module  : jplay.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JPLAY_C
#define JPLAY_C

/**
jplay  :  obj  ->
Play a sound object.
*/
PRIVATE void do_jplay(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    POP(env->stk);
    j_play(obj);
}
#endif
