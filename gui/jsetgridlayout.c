/*
    module  : 
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETGRIDLAYOUT_C
#define JSETGRIDLAYOUT_C

/**
jsetgridlayout  :  obj row col  ->
Adds a gridlayout manager to component obj with the specified rows and columns.
*/
PRIVATE void do_jsetgridlayout(pEnv env)
{
    int obj, row, col;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    THREEPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    INTEGER3(__func__);
    col = env->stk->u.num;
    POP(env->stk);
    row = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_setgridlayout(obj, row, col);
}
#endif
