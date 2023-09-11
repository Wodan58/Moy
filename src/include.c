/*
    module  : include.c
    version : 1.4
    date    : 09/11/23
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
#ifndef COMPILER
    Node node;

    PARM(1, STRTOD);
    node = lst_pop(env->stck);
    include(env, node.u.str, 1);
#endif
}
#endif
