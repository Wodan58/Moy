/*
    module  : time.c
    version : 1.4
    date    : 09/11/23
*/
#ifndef TIME_C
#define TIME_C

/**
OK 1140  time  :  A	->  I
Pushes the current time (in seconds since the Epoch).
*/
void time_(pEnv env)
{
#ifndef COMPILER
    Node node;

    node.u.num = time(0);
    node.op = INTEGER_;
    lst_push(env->stck, node);
#endif
}
#endif
