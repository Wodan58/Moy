/*
    module  : putchars.c
    version : 1.8
    date    : 03/05/24
*/
#ifndef PUTCHARS_C
#define PUTCHARS_C

/**
Q0  OK  3100  putchars  :  D  "abc.."  ->
[IMPURE] Writes abc.. (without quotes)
*/
void putchars_(pEnv env)
{
    Node node;

    PARM(1, STRTOD);
    env->stck = pvec_pop(env->stck, &node);
    if (!env->ignore)
	printf("%s", node.u.str);
}
#endif
