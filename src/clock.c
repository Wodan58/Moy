/*
    module  : clock.c
    version : 1.8
    date    : 02/01/24
*/
#ifndef CLOCK_C
#define CLOCK_C

/**
OK 1130  clock  :  A	->  I
[IMPURE] Pushes the integer value of current CPU usage in milliseconds.
*/
void clock_(pEnv env)
{
    Node node;

    if (env->ignore)
	node.u.num = 0;
    else
	node.u.num = ((clock() - env->startclock) * 1000) / CLOCKS_PER_SEC;
    node.op = INTEGER_;
    env->stck = pvec_add(env->stck, node);
}
#endif
