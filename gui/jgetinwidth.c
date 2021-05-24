/*
    module  : jgetinwidth.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JGETINWIDTH_C
#define JGETINWIDTH_C

/**
jgetinwidth  :  cont  ->  width
Returns the width of the client size.
*/
PRIVATE void do_jgetinwidth(pEnv env)
{
    int cont;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    cont = env->stk->u.num;
    env->stk->u.num = j_getinwidth(cont);
}
#endif
