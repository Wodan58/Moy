/*
    module  : recv.c
    version : 1.7
    date    : 01/18/24
*/
#ifndef RECV_C
#define RECV_C

/**
OK 3290  recv  :  A	P  ->  P  N
[MTH] Receive a node from a channel and push it on the stack.
*/
void recv_(pEnv env)
{
#ifdef USE_MULTI_THREADS_JOY
    Node temp, node;

    PARM(1, RECEIVE);
    temp = pvec_lst(env->stck);		/* receive a node from the channel, */ 
    if (receive(env, temp.u.num, &node))
	env->stck = pvec_add(env->stck, node);	/* push it on the stack */
    else {
	code(env, recv_);		/* reschedule this instruction */
	release(env);			/* switch to another task */
    }
#endif
}
#endif
