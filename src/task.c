/*
    module  : task.c
    version : 1.7
    date    : 01/18/24
*/
#ifndef TASK_C
#define TASK_C

/**
OK 3310  task  :  D	Q  ->
[MTH] Execute quotation Q in a separate thread.
*/
void task_(pEnv env)
{
#ifdef USE_MULTI_THREADS_JOY
    PARM(1, DIP);
    new_thread(env);		/* create a new thread, and switch to it */
#endif
}
#endif
