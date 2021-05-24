/*
    module  : 
    version : 1.1
    date    : 04/28/21
*/
#ifndef JGETFONTASCENT_C
#define JGETFONTASCENT_C

/**
jfontascent  :  obj  ->  ascent
Returns the ascent (space above the baseline) of the actual font of component
obj.
*/
PRIVATE void do_jgetfontascent(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    env->stk->u.num = j_getfontascent(obj);
}
#endif
