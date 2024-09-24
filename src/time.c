/*
    module  : time.c
    version : 1.10
    date    : 09/17/24
*/
#ifndef TIME_C
#define TIME_C

/**
Q0  IGNORE_PUSH  1140  time  :  A  ->  I
[IMPURE] Pushes the current time (in seconds since the Epoch).
*/
void time_(pEnv env)
{
    Node node;

    node.u.num = time(0);
    node.op = INTEGER_;
    vec_push(env->stck, node);
}
#endif
