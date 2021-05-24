/*
    module  : jmenubar.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JMENUBAR_C
#define JMENUBAR_C

/**
jmenubar  :  obj  ->  event
Creates a new menubar and returns its event number.
*/
PRIVATE void do_jmenubar(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    env->stk->u.num = j_menubar(obj);
}
#endif
