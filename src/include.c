/*
    module  : include.c
    version : 1.10
    date    : 03/15/21
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

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM("include");
    STRING("include");
    str = env->stk->u.str;
    POP(env->stk);
    include(str);
}
#endif
