/*
    module  : 
    version : 1.1
    date    : 04/28/21
*/
#ifndef JGETSTRINGWIDTH_C
#define JGETSTRINGWIDTH_C

/**
jgetstringwidth  :  obj str  ->  length
Returns the length of str of the actual font of component obj.
*/
PRIVATE void do_jgetstringwidth(pEnv env)
{
    int obj;
    char *str;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    STRING(__func__);
    INTEGER2(__func__);
    str = env->stk->u.str;
    POP(env->stk);
    obj = env->stk->u.num;
    env->stk->u.num = j_getstringwidth(obj, str);
}
#endif
