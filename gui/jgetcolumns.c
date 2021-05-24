/*
    module  : jgetcolumns.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JGETCOLUMNS_C
#define JGETCOLUMNS_C

/**
jgetcolumns  :  obj  ->  columns
Gets the number of columns in obj.
*/
PRIVATE void do_jgetcolumns(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    env->stk->u.num = j_getcolumns(obj);
}
#endif
