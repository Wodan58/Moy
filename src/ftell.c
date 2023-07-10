/*
    module  : ftell.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef FTELL_C
#define FTELL_C

/**
OK 2000  ftell  :  DAA	S  ->  S I
I is the current position of stream S.
*/
void ftell_(pEnv env)
{
    Node node;

    PARM(1, FGET);
    node = vec_back(env->stck);
    node.u.num = ftell(node.u.fil);
    node.op = INTEGER_;
    vec_push(env->stck, node);    
}
#endif
