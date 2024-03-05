/*
    module  : abort.c
    version : 1.9
    date    : 03/05/24
*/
#ifndef ABORT_C
#define ABORT_C

/**
Q0  OK  3120  abort  :  N  ->
Aborts execution of current Joy program, returns to Joy main cycle.
*/
void abort_(pEnv env)
{
    abortexecution_(MY_ABORT);
    /* nothing */
}
#endif
