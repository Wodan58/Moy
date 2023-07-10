/*
    module  : manual.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef MANUAL_C
#define MANUAL_C

/**
OK 2950  manual  :  N	->
Writes this manual of all Joy primitives to output file.
*/
void manual_(pEnv env)
{
    make_manual(0);
    env->nothing++;
}
#endif
