/*
    module  : fgetch.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef FGETCH_C
#define FGETCH_C

/**
OK 1880  fgetch  :  DAA	S  ->  S C
C is the next available character from stream S.
*/
void fgetch_(pEnv env)
{
    Node node;

    PARM(1, FGET);
    node = vec_back(env->stck);
    node.u.num = getc(node.u.fil);
    node.op = CHAR_;
    vec_push(env->stck, node);    
}
#endif
