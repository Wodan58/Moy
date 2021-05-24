/*
    module  : jisresizable.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JISRESIZABLE_C
#define JISRESIZABLE_C

/**
jisresizable  :  obj  ->  status
Returns true if component is resizable, false otherwise.
*/
PRIVATE void do_jisresizable(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    env->stk->u.num = j_isresizable(obj);
}
#endif
