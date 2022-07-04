/*
    module  : frename.c
    version : 1.11
    date    : 06/20/22
*/
#ifndef FRENAME_C
#define FRENAME_C

/**
frename  :  P1 P2  ->  B
The file system object with pathname P1 is renamed to P2.
B is a boolean indicating success or failure.
*/
PRIVATE void do_frename(pEnv env)
{
    COMPILE;
    TWOPARAMS("frename");
    STRING("frename");
    STRING2("frename");
    BINARY(BOOLEAN_NEWNODE, !rename(env->stk->next->u.str, env->stk->u.str));
}
#endif
