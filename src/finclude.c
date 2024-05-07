/*
    module  : finclude.c
    version : 1.11
    date    : 05/02/24
*/
#ifndef FINCLUDE_C
#define FINCLUDE_C

/**
Q0  OK  3160  finclude  :  DU  S  ->  F ...
[FOREIGN] Reads Joy source code from stream S and pushes it onto stack.
*/
void finclude_(pEnv env)
{
    Node node;

    PARM(1, STRTOD);
    env->stck = pvec_pop(env->stck, &node);	/* remove file name */
    include(env, node.u.str);
    env->finclude_busy = 1;		/* tell scanner about finclude */
    if (setjmp(env->finclude))
	env->finclude_busy = 0;		/* done with finclude */
    else while (1)
	get_(env);			/* read all factors from file */
}
#endif
