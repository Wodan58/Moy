/*
    module  : fputch.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef FPUTCH_C
#define FPUTCH_C

/**
OK 1960  fputch  :  DDA	S C  ->  S
The character C is written to the current position of stream S.
*/
void fputch_(pEnv env)
{
    Node node, elem;

    PARM(2, FREAD);
    elem = vec_pop(env->stck);
    node = vec_back(env->stck);
    putc(elem.u.num, node.u.fil);
}
#endif
