/*
    module  : jgetstate.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JGETSTATE_C
#define JGETSTATE_C

/**
jgetstate  :  obj  ->  state
Returns J_TRUE, if component is selected, J_FALSE otherwise.
*/
PRIVATE void do_jgetstate(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    env->stk->u.num = j_getstate(obj);
}
#endif
