/*
    module  : abort.c
    version : 1.5
    date    : 09/15/23
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
