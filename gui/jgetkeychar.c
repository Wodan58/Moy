/*
    module  : jgetkeychar.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JGETKEYCHAR_C
#define JGETKEYCHAR_C

/**
jgetkeychar  :  obj  ->  ascii
Return the ascii value of the last key pressed.
*/
PRIVATE void do_jgetkeychar(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    env->stk->u.num = j_getkeychar(obj);
}
#endif
