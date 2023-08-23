/*
    module  : fputch.c
    version : 1.2
    date    : 08/23/23
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
    elem = lst_pop(env->stck);
    node = lst_back(env->stck);
    putc(elem.u.num, node.u.fil);
}
#endif
