/*
    module  : time.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef TIME_C
#define TIME_C

/**
OK 1140  time  :  A	->  I
Pushes the current time (in seconds since the Epoch).
*/
void time_(pEnv env)
{
    Node node;

    node.u.num = time(0);
    node.op = INTEGER_;
    vec_push(env->stck, node);
}
#endif
