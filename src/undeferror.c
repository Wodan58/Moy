/*
    module  : undeferror.c
    version : 1.7
    date    : 03/05/24
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
    env->stck = pvec_add(env->stck, node);
}
#endif
