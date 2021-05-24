/*
    module  : jdelete.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JDELETE_C
#define JDELETE_C

/**
jdelete  :  obj start end  ->
Deletes text from starting position start to ending position end.
*/
PRIVATE void do_jdelete(pEnv env)
{
    int obj, start, end;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    THREEPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    INTEGER3(__func__);
    end = env->stk->u.num;
    POP(env->stk);
    start = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_delete(obj, start, end);
}
#endif
