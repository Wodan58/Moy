/*
    module  : jgetselstart.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JGETSELSTART_C
#define JGETSELSTART_C

/**
jgetselstart  :  obj  ->  position
Returns the initial position of any selected text.
*/
PRIVATE void do_jgetselstart(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    env->stk->u.num = j_getselstart(obj);
}
#endif
