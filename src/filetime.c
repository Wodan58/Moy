/*
    module  : filetime.c
    version : 1.13
    date    : 06/22/24
*/
#ifndef FILETIME_C
#define FILETIME_C

#include <sys/stat.h>

/**
Q0  OK  3160  filetime  :  DA  F  ->  T
[FOREIGN] T is the modification time of file F.
*/
void filetime_(pEnv env)
{
    Node node;
    struct stat buf;

    PARM(1, STRTOD);
    env->stck = pvec_pop(env->stck, &node);
    if (stat(node.u.str, &buf) == -1)
	node.u.num = 0;
    else
	node.u.num = buf.st_mtime;
    node.op = INTEGER_;
    env->stck = pvec_add(env->stck, node);
}
#endif
