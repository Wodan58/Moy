/*
    module  : jsetcolumns.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETCOLUMNS_C
#define JSETCOLUMNS_C

/**
jsetcolumns  :  obj columns  ->
Sets the number of columns for obj to columns.
*/
PRIVATE void do_jsetcolumns(pEnv env)
{
    int obj, columns;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    columns = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_setcolumns(obj, columns);
}
#endif
