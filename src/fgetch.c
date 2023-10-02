/*
    module  : fgetch.c
    version : 1.7
    date    : 10/02/23
*/
#ifndef FGETCH_C
#define FGETCH_C

/**
OK 1870  fgetch  :  A	S  ->  S C
C is the next available character from stream S.
*/
void fgetch_(pEnv env)
{
    Node node;

    PARM(1, FGET);
    node = pvec_lst(env->stck);
    node.u.num = getc(node.u.fil);
    node.op = CHAR_;
    env->stck = pvec_add(env->stck, node);
}
#endif
