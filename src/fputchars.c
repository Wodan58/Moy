/*
    module  : fputchars.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef FPUTCHARS_C
#define FPUTCHARS_C

/**
OK 1970  fputchars  :  DDA 	S "abc.."  ->  S
The string abc.. (no quotes) is written to the current position of stream S.
*/
void fputchars_(pEnv env) /* suggested by Heiko Kuhrt, as "fputstring_" */
{
    Node node, elem;

    PARM(2, FPUTCHARS);
    elem = vec_pop(env->stck);
    node = vec_back(env->stck);
    fprintf(node.u.fil, "%s", elem.u.str);
}
#endif
