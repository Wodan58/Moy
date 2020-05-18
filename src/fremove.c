/*
    module  : fremove.c
    version : 1.9
    date    : 03/28/20
*/
#ifndef FREMOVE_C
#define FREMOVE_C

/**
fremove  :  P  ->  B
The file system object with pathname P is removed from the file system.
B is a boolean indicating success or failure.
*/
PRIVATE void do_fremove(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM("fremove");
    STRING("fremove");
    stk->next->u.num = !remove(stk->u.str);
    stk->next->op = BOOLEAN_;
    POP(stk);
}
#endif
