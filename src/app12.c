/*
    module  : app12.c
    version : 1.11
    date    : 06/20/22
*/
#ifndef APP12_C
#define APP12_C

/**
app12  :  X Y1 Y2 [P]  ->  R1 R2
Executes P twice, with Y1 and Y2, returns R1 and R2.
*/
PRIVATE void do_app12(pEnv env)
{
    FOURPARAMS("app12");
    do_unary2(env);
    env->stk->next->next = env->stk->next->next->next; /* delete X */
}
#endif
