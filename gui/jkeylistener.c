/*
    module  : jkeylistener.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JKEYLISTENER_C
#define JKEYLISTENER_C

/**
jkeylistener  :  obj  ->  event
Adds a new key listener to component obj, and returns its event number.
*/
PRIVATE void do_jkeylistener(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    env->stk->u.num = j_keylistener(obj);
}
#endif
