/*
    module  : filetime.c
    version : 1.11
    date    : 06/20/22
*/
#ifndef FILETIME_C
#define FILETIME_C

#ifndef COSMO
#include <sys/stat.h>
#endif

/**
filetime  :  F  ->  T
T is the modification time of file F.
*/
PRIVATE void do_filetime(pEnv env)
{
    struct stat buf;

    COMPILE;
    ONEPARAM("filetime");
    if (stat(env->stk->u.str, &buf) == -1)
	buf.st_mtime = 0;
    UNARY(INTEGER_NEWNODE, buf.st_mtime);
}
#endif
