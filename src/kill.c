/*
    module  : kill.c
    version : 1.6
    date    : 01/18/24
*/
#ifndef KILL_C
#define KILL_C

/**
OK 3280  kill  :  N	->
[MTH] Make all threads eligible for garbage collection.
*/
void kill_(pEnv env)
{
#ifdef USE_MULTI_THREADS_JOY
    kill_thread(env);		/* exit a thread */
#endif
}
#endif
