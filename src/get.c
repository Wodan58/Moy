/*
    module  : get.c
    version : 1.9
    date    : 09/17/24
*/
#ifndef GET_C
#define GET_C

/**
Q0  POSTPONE  3070  get  :  A  ->  F
[IMPURE] Reads a factor from input and pushes it onto stack.
*/
void get_(pEnv env)
{
    env->token = yylex(env);
    readfactor(env);
}
#endif
