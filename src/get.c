/*
    module  : get.c
    version : 1.12
    date    : 03/15/21
*/
#ifndef GET_C
#define GET_C

/**
get  :  ->  F
Reads a factor from input and pushes it onto stack.
*/
PRIVATE void do_get(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    readfactor(env, yylex());
}
#endif
