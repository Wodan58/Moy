/*
    module  : abort.c
    version : 1.8
    date    : 02/01/24
*/
#ifndef ABORT_C
#define ABORT_C

/**
OK 3120  abort  :  N	->
Aborts execution of current Joy program, returns to Joy main cycle.
*/
void abort_(pEnv env)
{
    abortexecution_(MY_ABORT);
    /* nothing */
}
#endif
