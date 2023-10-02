/*
    module  : feof.c
    version : 1.7
    date    : 10/02/23
*/
#ifndef FEOF_C
#define FEOF_C

/**
OK 1840  feof  :  A	S  ->  S B
B is the end-of-file status of stream S.
*/
void feof_(pEnv env)
{
    Node node;

    PARM(1, FGET);
    node = pvec_lst(env->stck);
    node.u.num = feof(node.u.fil);
    node.op = BOOLEAN_;
    env->stck = pvec_add(env->stck, node);
}
#endif
