/*
    module  : include.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef INCLUDE_C
#define INCLUDE_C

/**
OK 3110  include  :  D	"filnam.ext"  ->
Transfers input to file whose name is "filnam.ext".
On end-of-file returns to previous input file.
*/
void include_(pEnv env)
{
    Node node;

    PARM(1, STRTOD);
    env->stck = pvec_pop(env->stck, &node);
    include(env, node.u.str, 1);
}
#endif
