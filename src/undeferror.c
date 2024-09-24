/*
    module  : undeferror.c
    version : 1.8
    date    : 09/17/24
*/
#ifndef UNDEFERROR_C
#define UNDEFERROR_C

/**
Q0  OK  1100  undeferror  :  A  ->  I
Pushes current value of undefined-is-error flag.
*/
void undeferror_(pEnv env)
{
    Node node;

    node.u.num = env->undeferror;
    node.op = INTEGER_;
    vec_push(env->stck, node);
}
#endif
