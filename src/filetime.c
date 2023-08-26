/*
    module  : filetime.c
    version : 1.4
    date    : 08/26/23
*/
#ifndef FILETIME_C
#define FILETIME_C

#include <sys/stat.h>

/**
OK 1943  filetime  :  DA 	F  ->  T
T is the modification time of file F.
*/
void filetime_(pEnv env)
{
    Node node;
    struct stat buf;

    PARM(1, STRTOD);
    node = lst_pop(env->stck);
    if (stat(node.u.str, &buf) == -1)
        node.u.num = 0;
    else
        node.u.num = buf.st_mtime;
    node.op = INTEGER_;
    lst_push(env->stck, node);
}
#endif
