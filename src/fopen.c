/*
    module  : fopen.c
    version : 1.11
    date    : 06/20/22
*/
#ifndef FOPEN_C
#define FOPEN_C

/**
fopen  :  P M  ->  S
The file system object with pathname P is opened with mode M (r, w, a, etc.)
and stream object S is pushed; if the open fails, file:NULL is pushed.
*/
PRIVATE void do_fopen(pEnv env)
{
    COMPILE;
    TWOPARAMS("fopen");
    STRING("fopen");
    STRING2("fopen");
    BINARY(FILE_NEWNODE, fopen(env->stk->next->u.str, env->stk->u.str));
}
#endif
