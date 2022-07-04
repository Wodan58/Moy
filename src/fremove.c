/*
    module  : fremove.c
    version : 1.11
    date    : 06/20/22
*/
#ifndef FREMOVE_C
#define FREMOVE_C

/**
fremove  :  P  ->  B
The file system object with pathname P is removed from the file system.
B is a boolean indicating success or failure.
*/
PRIVATE void do_fremove(pEnv env)
{
    COMPILE;
    ONEPARAM("fremove");
    STRING("fremove");
    UNARY(BOOLEAN_NEWNODE, !remove(env->stk->u.str));
}
#endif
