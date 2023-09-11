/*
    module  : fgetch.c
    version : 1.5
    date    : 09/11/23
*/
#ifndef FGETCH_C
#define FGETCH_C

/**
OK 1870  fgetch  :  A	S  ->  S C
C is the next available character from stream S.
*/
void fgetch_(pEnv env)
{
#ifndef COMPILER
    Node node;

    PARM(1, FGET);
    node = lst_back(env->stck);
    node.u.num = getc(node.u.fil);
    node.op = CHAR_;
    lst_push(env->stck, node);    
#endif
}
#endif
