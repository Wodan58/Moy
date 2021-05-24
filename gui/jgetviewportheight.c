/*
    module  : 
    version : 1.1
    date    : 04/28/21
*/
#ifndef JGETVIEWPORTHEIGHT_C
#define JGETVIEWPORTHEIGHT_C

/**
jgetviewportheight  :  obj  ->  height
Returns the height of the component's obj port (the area that is shown).
*/
PRIVATE void do_jgetviewportheight(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    env->stk->u.num = j_getviewportheight(obj);
}
#endif
