/*
    module  : include.c
    version : 1.2
    date    : 08/23/23
*/
#ifndef INCLUDE_C
#define INCLUDE_C

/**
OK 3140  include  :  D	"filnam.ext"  ->
Transfers input to file whose name is "filnam.ext".
On end-of-file returns to previous input file.
*/
void include_(pEnv env)
{
    Node node;

    PARM(1, STRTOD);
    node = lst_pop(env->stck);
    include(env, node.u.str, 1);
}
#endif
