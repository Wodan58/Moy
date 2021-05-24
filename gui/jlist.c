/*
    module  : jlist.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JLIST_C
#define JLIST_C

/**
jlist  :  obj rows  ->  event
Creates a new list component with the specified number of rows and returns its
event number.
*/
PRIVATE void do_jlist(pEnv env)
{
    int obj, rows;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    rows = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    env->stk->u.num = j_list(obj, rows);
}
#endif
