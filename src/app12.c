/*
    module  : app12.c
    version : 1.10
    date    : 03/15/21
*/
#ifndef APP12_C
#define APP12_C

/**
app12  :  X Y1 Y2 [P]  ->  R1 R2
Executes P twice, with Y1 and Y2, returns R1 and R2.
*/
PRIVATE void do_app12(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    THREEPARAMS("app12");
    do_unary2(env);
    env->stk->next->next = env->stk->next->next->next;
}
#endif
