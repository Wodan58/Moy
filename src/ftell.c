/*
    module  : ftell.c
    version : 1.2
    date    : 08/23/23
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
    node = lst_back(env->stck);
    node.u.num = ftell(node.u.fil);
    node.op = INTEGER_;
    lst_push(env->stck, node);    
}
#endif
