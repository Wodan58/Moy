/*
    module  : abort.c
    version : 1.10
    date    : 03/21/24
*/
#ifndef ABORT_C
#define ABORT_C

/**
Q0  IGNORE_OK  3120  abort  :  N  ->
Aborts execution of current Joy program, returns to Joy main cycle.
*/
void abort_(pEnv env)
{
    abortexecution_(ABORT_RETRY);
}
#endif
