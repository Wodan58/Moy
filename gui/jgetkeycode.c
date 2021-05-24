/*
    module  : jgetkeycode.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JGETKEYCODE_C
#define JGETKEYCODE_C

/**
jgetkeycode  :  obj  ->  code
Return the integer key code of the last key pressed.
*/
PRIVATE void do_jgetkeycode(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    env->stk->u.num = j_getkeycode(obj);
}
#endif
