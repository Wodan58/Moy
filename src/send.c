/*
    module  : send.c
    version : 1.11
    date    : 03/05/24
*/
#ifndef SEND_C
#define SEND_C

/**
Q0  OK  3280  send  :  D  C  N  ->  C
[MTH] Send a node through a channel and switch to the next task.
*/
void send_(pEnv env)
{
#ifdef USE_MULTI_THREADS_JOY
    Node node, temp;

    PARM(2, SEND);
    env->stck = pvec_pop(env->stck, &node);  /* read the node from the stack */
    temp = pvec_lst(env->stck);		/* send the node through the channel */
    send(env, temp.u.num, node);	/* use channel number */
#endif
}
#endif
