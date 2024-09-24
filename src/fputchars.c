/*
    module  : fputchars.c
    version : 1.10
    date    : 09/17/24
*/
#ifndef FPUTCHARS_C
#define FPUTCHARS_C

/**
Q0  OK  1960  fputchars  :  D  S "abc.."  ->  S
[FOREIGN] The string abc.. (no quotes) is written to the current position of
stream S.
*/
void fputchars_(pEnv env)	/* suggested by Heiko Kuhrt, as "fputstring_" */
{
    Node elem, node;

    PARM(2, FPUTCHARS);
    elem = vec_pop(env->stck);
    node = vec_back(env->stck);
    fprintf(node.u.fil, "%s", elem.u.str);
}
#endif
