/*
    module  : kill.c
    version : 1.9
    date    : 03/05/24
*/
#ifndef KILL_C
#define KILL_C

/**
Q0  OK  3250  kill  :  N  ->
[MTH] Make all threads eligible for garbage collection.
*/
void kill_(pEnv env)
{
#ifdef USE_MULTI_THREADS_JOY
    kill_thread(env);		/* exit a thread */
#endif
}
#endif
