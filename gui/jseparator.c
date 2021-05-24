/*
    module  : jseparator.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSEPARATOR_C
#define JSEPARATOR_C

/**
jseparator  :  obj  ->
Adds a separator bar to the component obj.
*/
PRIVATE void do_jseparator(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    POP(env->stk);
    j_separator(obj);
}
#endif
