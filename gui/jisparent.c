/*
    module  : jisparent.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JISPARENT_C
#define JISPARENT_C

/**
jisparent  :  obj cont  ->  status
Returns J_TRUE if cont is parent of obj, J_FALSE otherwise.
*/
PRIVATE void do_jisparent(pEnv env)
{
    int obj, cont;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    cont = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    env->stk->u.num = j_isparent(obj, cont);
}
#endif
