/*
    module  : clock.c
    version : 1.2
    date    : 08/21/23
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
    vec_push(env->stck, node);
}
#endif
