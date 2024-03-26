/*
    module  : task.c
    version : 1.10
    date    : 03/05/24
*/
#ifndef TASK_C
#define TASK_C

/**
Q0  OK  3270  task  :  D  Q  ->
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
