/*
    module  : putchars.c
    version : 1.7
    date    : 02/01/24
*/
#ifndef PUTCHARS_C
#define PUTCHARS_C

/**
OK 3100  putchars  :  D	"abc.."  ->
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
