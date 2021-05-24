/*
    module  : jradiogroup.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JRADIOGROUP_C
#define JRADIOGROUP_C

/**
jradiogroup  :  obj  ->  event
Creates a new radiogroup and returns its event number.
*/
PRIVATE void do_jradiogroup(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    env->stk->u.num = j_radiogroup(obj);
}
#endif
