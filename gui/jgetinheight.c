/*
    module  : jgetinheight.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JGETINHEIGHT_C
#define JGETINHEIGHT_C

/**
jgetinheight  :  cont  ->  height
Returns the height of the client size.
*/
PRIVATE void do_jgetinheight(pEnv env)
{
    int cont;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    cont = env->stk->u.num;
    env->stk->u.num = j_getinheight(cont);
}
#endif
