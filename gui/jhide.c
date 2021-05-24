/*
    module  : jhide.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JHIDE_C
#define JHIDE_C

/**
jhide  :  obj  ->
Hides the component obj.
*/
PRIVATE void do_jhide(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    j_hide(obj);
}
#endif
