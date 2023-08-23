/*
    module  : ferror.c
    version : 1.2
    date    : 08/23/23
*/
#ifndef FERROR_C
#define FERROR_C

/**
OK 1850  ferror  :  DAA	S  ->  S B
B is the error status of stream S.
*/
void ferror_(pEnv env)
{
    Node node;

    PARM(1, FGET);
    node = lst_back(env->stck);
    node.u.num = ferror(node.u.fil);
    node.op = BOOLEAN_;
    lst_push(env->stck, node);    
}
#endif
