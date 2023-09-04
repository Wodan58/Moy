/*
    module  : abort.c
    version : 1.3
    date    : 09/04/23
*/
#ifndef ABORT_C
#define ABORT_C

/**
OK 3120  abort  :  N	->
Aborts execution of current Joy program, returns to Joy main cycle.
*/
void abort_(pEnv env)
{
    env->nothing++;
    abortexecution_(MY_ABORT);
}
#endif
