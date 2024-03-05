/*
    module  : time.c
    version : 1.8
    date    : 03/05/24
*/
#ifndef TIME_C
#define TIME_C

/**
Q0  OK  1140  time  :  A  ->  I
[IMPURE] Pushes the current time (in seconds since the Epoch).
*/
void time_(pEnv env)
{
    Node node;

    if (env->ignore)
	node.u.num = 0;
    else
	node.u.num = time(0);
    node.op = INTEGER_;
    env->stck = pvec_add(env->stck, node);
}
#endif
