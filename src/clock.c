/*
    module  : clock.c
    version : 1.7
    date    : 10/02/23
*/
#ifndef CLOCK_C
#define CLOCK_C

/**
OK 1130  clock  :  A	->  I
Pushes the integer value of current CPU usage in milliseconds.
*/
void clock_(pEnv env)
{
    Node node;

    node.u.num = ((clock() - env->startclock) * 1000) / CLOCKS_PER_SEC;
    node.op = INTEGER_;
    env->stck = pvec_add(env->stck, node);
}
#endif
