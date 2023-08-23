/*
    module  : feof.c
    version : 1.2
    date    : 08/23/23
*/
#ifndef FEOF_C
#define FEOF_C

/**
OK 1840  feof  :  DAA	S  ->  S B
B is the end-of-file status of stream S.
*/
void feof_(pEnv env)
{
    Node node;

    PARM(1, FGET);
    node = lst_back(env->stck);
    node.u.num = feof(node.u.fil);
    node.op = BOOLEAN_;
    lst_push(env->stck, node);    
}
#endif
