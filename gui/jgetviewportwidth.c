/*
    module  : 
    version : 1.1
    date    : 04/28/21
*/
#ifndef JGETVIEWPORTWIDTH_C
#define JGETVIEWPORTWIDTH_C

/**
jgetviewportwidth  :  obj  ->  width
Returns the width of the component's obj port (the area that is shown).
*/
PRIVATE void do_jgetviewportwidth(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    env->stk->u.num = j_getviewportwidth(obj);
}
#endif
