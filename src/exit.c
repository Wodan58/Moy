/*
    module  : exit.c
    version : 1.9
    date    : 03/05/24
*/
#ifndef EXIT_C
#define EXIT_C

/**
Q0  OK  3240  exit  :  N  ->
[MTH] Exit a thread.
*/
void exit_(pEnv env)
{
#ifdef USE_MULTI_THREADS_JOY
    exit_thread(env);		/* exit a thread */
#endif
}
#endif
