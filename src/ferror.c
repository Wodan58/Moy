/*
    module  : ferror.c
    version : 1.10
    date    : 09/17/24
*/
#ifndef FERROR_C
#define FERROR_C

/**
Q0  OK  1850  ferror  :  A  S  ->  S B
[FOREIGN] B is the error status of stream S.
*/
void ferror_(pEnv env)
{
    Node node;

    PARM(1, FGET);
    node = vec_back(env->stck);
    node.u.num = ferror(node.u.fil);
    node.op = BOOLEAN_;
    vec_push(env->stck, node);
}
#endif
