/*
    module  : setecho.c
    version : 1.7
    date    : 02/01/24
*/
#ifndef SETECHO_C
#define SETECHO_C

/**
OK 3000  setecho  :  D	I  ->
[IMPURE] Sets value of echo flag for listing.
I = 0: no echo, 1: echo, 2: with tab, 3: and linenumber.
*/
void setecho_(pEnv env)
{
    Node node;

    PARM(1, PREDSUCC);
    env->stck = pvec_pop(env->stck, &node);
    if (!env->ignore && !env->echoflag_set)
	env->echoflag = node.u.num;
}
#endif
