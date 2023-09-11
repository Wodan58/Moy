/*
    module  : fputchars.c
    version : 1.5
    date    : 09/11/23
*/
#ifndef FPUTCHARS_C
#define FPUTCHARS_C

/**
OK 1960  fputchars  :  D 	S "abc.."  ->  S
The string abc.. (no quotes) is written to the current position of stream S.
*/
void fputchars_(pEnv env) /* suggested by Heiko Kuhrt, as "fputstring_" */
{
#ifndef COMPILER
    Node node, elem;

    PARM(2, FPUTCHARS);
    elem = lst_pop(env->stck);
    node = lst_back(env->stck);
    fprintf(node.u.fil, "%s", elem.u.str);
#endif
}
#endif
