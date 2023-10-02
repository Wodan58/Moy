/*
    module  : get.c
    version : 1.5
    date    : 10/02/23
*/
#ifndef GET_C
#define GET_C

/**
OK 3070  get  :  A 	->  F
Reads a factor from input and pushes it onto stack.
*/
PRIVATE void get_(pEnv env)
{
    env->token = yylex(env);
    readfactor(env);
}
#endif
