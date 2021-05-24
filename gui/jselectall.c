/*
    module  : jselectall.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSELECTALL_C
#define JSELECTALL_C

/**
jselectall  :  obj  ->
Selects all the text in the component obj.
*/
PRIVATE void do_jselectall(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    POP(env->stk);
    j_selectall(obj);
}
#endif
