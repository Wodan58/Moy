/*
    module  : putchars.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef PUTCHARS_C
#define PUTCHARS_C

/**
OK 3130  putchars  :  D	"abc.."  ->
Writes abc.. (without quotes)
*/
void putchars_(pEnv env)
{
    Node node;

    PARM(1, STRTOD);
    node = vec_pop(env->stck);
    printf("%s", node.u.str);
}
#endif
