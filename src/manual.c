/*
    module  : manual.c
    version : 1.2
    date    : 09/04/23
*/
#ifndef MANUAL_C
#define MANUAL_C

/**
OK 2930  manual  :  N	->
Writes this manual of all Joy primitives to output file.
*/
void manual_(pEnv env)
{
    make_manual(0);
    env->nothing++;
}
#endif
