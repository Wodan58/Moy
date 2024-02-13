/*
    module  : ftell.c
    version : 1.8
    date    : 02/01/24
*/
#ifndef FTELL_C
#define FTELL_C

/**
OK 1990  ftell  :  A	S  ->  S I
[FOREIGN] I is the current position of stream S.
*/
void ftell_(pEnv env)
{
    Node node;

    PARM(1, FGET);
    node = pvec_lst(env->stck);
    node.u.num = ftell(node.u.fil);
    node.op = INTEGER_;
    env->stck = pvec_add(env->stck, node);
}
#endif
