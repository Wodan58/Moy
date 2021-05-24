/*
    module  : jgetpos.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JGETPOS_C
#define JGETPOS_C

/**
jgetpos  :  obj  ->  xpos ypos
Returns the current position (xpos, ypos).
*/
PRIVATE void do_jgetpos(pEnv env)
{
    int obj, xpos, ypos;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    j_getpos(obj, &xpos, &ypos);
    env->stk->u.num = xpos;
    PUSH_NUM(INTEGER_, ypos);
}
#endif
