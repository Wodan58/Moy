/*
    module  : putchars.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef PUTCHARS_C
#define PUTCHARS_C

/**
OK 3100  putchars  :  D	"abc.."  ->
Writes abc.. (without quotes)
*/
void putchars_(pEnv env)
{
    Node node;

    PARM(1, STRTOD);
    env->stck = pvec_pop(env->stck, &node);
    printf("%s", node.u.str);
}
#endif
