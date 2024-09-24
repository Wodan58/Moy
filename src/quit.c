/*
    module  : quit.c
    version : 1.15
    date    : 09/17/24
*/
#ifndef QUIT_C
#define QUIT_C

/**
Q0  IGNORE_OK  3130  quit  :  N  ->
Exit from Joy.
*/
void quit_(pEnv env)
{
    abortexecution_(ABORT_QUIT);
}	/* LCOV_EXCL_LINE */
#endif
