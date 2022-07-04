/*
    module  : include.c
    version : 1.11
    date    : 06/20/22
*/
#ifndef INCLUDE_C
#define INCLUDE_C

/**
include  :  "filnam.ext"  ->
Transfers input to file whose name is "filnam.ext".
On end-of-file returns to previous input file.
*/
PRIVATE void do_include(pEnv env)
{
    char *str;

    ONEPARAM("include");
    STRING("include");
    str = env->stk->u.str;
    POP(env->stk);
    include(env, str, 1);
}
#endif
