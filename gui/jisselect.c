/*
    module  : jisselect.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JISSELECT_C
#define JISSELECT_C

/**
jisselect  :  obj item  ->  status
Returns J_TRUE if the particular item is currently selected, J_FALSE otherwise.
*/
PRIVATE void do_jisselect(pEnv env)
{
    int obj, item;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    item = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    env->stk->u.num = j_isselect(obj, item);
}
#endif
