/*
    module  : filetime.c
    version : 1.6
    date    : 09/11/23
*/
#ifndef FILETIME_C
#define FILETIME_C

#include <sys/stat.h>

/**
OK 3190  filetime  :  DA 	F  ->  T
[EXT] T is the modification time of file F.
*/
void filetime_(pEnv env)
{
#ifndef COMPILER
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
#endif
}
#endif
