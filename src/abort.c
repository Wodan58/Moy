/*
    module  : abort.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef ABORT_C
#define ABORT_C

/**
OK 3150  abort  :  N	->
Aborts execution of current Joy program, returns to Joy main cycle.
*/
void abort_(pEnv env)
{
    env->nothing++;
    abortexecution_();
}
#endif
