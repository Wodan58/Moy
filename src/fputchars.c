/*
    module  : fputchars.c
    version : 1.9
    date    : 03/05/24
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
    Node node, elem;

    PARM(2, FPUTCHARS);
    env->stck = pvec_pop(env->stck, &elem);
    node = pvec_lst(env->stck);
    fprintf(node.u.fil, "%s", elem.u.str);
}
#endif
