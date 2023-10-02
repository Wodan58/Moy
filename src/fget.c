/*
    module  : fget.c
    version : 1.7
    date    : 10/02/23
*/
#ifndef FGET_C
#define FGET_C

/**
OK 3180  fget  :  A	S  ->  S F
[EXT] Reads a factor from stream S and pushes it onto stack.
*/
void fget_(pEnv env)
{
    Node node;

    PARM(1, FGET);
    node = pvec_lst(env->stck);
    if (redirect(env->filename, "fget", node.u.fil)) {	/* switch file */
	env->token = yylex(env);
	readfactor(env);
    }
}
#endif
