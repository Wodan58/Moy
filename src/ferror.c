/*
    module  : ferror.c
    version : 1.7
    date    : 10/02/23
*/
#ifndef FERROR_C
#define FERROR_C

/**
OK 1850  ferror  :  A	S  ->  S B
B is the error status of stream S.
*/
void ferror_(pEnv env)
{
    Node node;

    PARM(1, FGET);
    node = pvec_lst(env->stck);
    node.u.num = ferror(node.u.fil);
    node.op = BOOLEAN_;
    env->stck = pvec_add(env->stck, node);
}
#endif
