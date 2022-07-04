/*
    module  : get.c
    version : 1.13
    date    : 06/20/22
*/
#ifndef GET_C
#define GET_C

/**
get  :  ->  F
Reads a factor from input and pushes it onto stack.
*/
PRIVATE void do_get(pEnv env)
{
    COMPILE;
    readfactor(env, yylex(env));
}
#endif
