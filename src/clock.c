/*
    module  : clock.c
    version : 1.10
    date    : 03/21/24
*/
#ifndef CLOCK_C
#define CLOCK_C

/**
Q0  IGNORE_PUSH  1130  clock  :  A  ->  I
[IMPURE] Pushes the integer value of current CPU usage in milliseconds.
*/
void clock_(pEnv env)
{
    Node node;

    node.u.num = ((clock() - env->startclock) * 1000) / CLOCKS_PER_SEC;
    node.op = INTEGER_;
    env->stck = pvec_add(env->stck, node);
}
#endif
