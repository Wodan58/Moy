/*
    module  : jchoice.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JCHOICE_C
#define JCHOICE_C

/**
jchoice  :  obj  ->  event
Creates a new choice component and returns its event number.
*/
PRIVATE void do_jchoice(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    env->stk->u.num = j_choice(obj);
}
#endif
