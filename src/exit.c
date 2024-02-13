/*
    module  : exit.c
    version : 1.6
    date    : 01/18/24
*/
#ifndef EXIT_C
#define EXIT_C

/**
OK 3270  exit  :  N	->
[MTH] Exit a thread.
*/
void exit_(pEnv env)
{
#ifdef USE_MULTI_THREADS_JOY
    exit_thread(env);		/* exit a thread */
#endif
}
#endif
