/*
    module  : filetime.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef FILETIME_C
#define FILETIME_C

#ifndef COSMO
#include <sys/stat.h>
#endif

/**
OK 3210  filetime  :  DA 	F  ->  T
T is the modification time of file F.
*/
void filetime_(pEnv env)
{
    Node node;
    struct stat buf;

    PARM(1, STRTOD);
    node = vec_pop(env->stck);
    if (stat(node.u.str, &buf) == -1)
        node.u.num = 0;
    else
        node.u.num = buf.st_mtime;
    node.op = INTEGER_;
    vec_push(env->stck, node);
}
#endif
