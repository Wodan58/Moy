/*
    module  : jisvisible.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JISVISIBLE_C
#define JISVISIBLE_C

/**
jisvisible  :  obj  ->  status
Returns J_TRUE if obj is visible, J_FALSE otherwise.
*/
PRIVATE void do_jisvisible(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    env->stk->u.num = j_isvisible(obj);
}
#endif
