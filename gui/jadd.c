/*
    module  : jadd.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JADD_C
#define JADD_C

/**
jadd  :  obj cont  ->
Adds component obj to container cont.
*/
PRIVATE void do_jadd(pEnv env)
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
    POP(env->stk);
    j_add(obj, cont);
}
#endif
