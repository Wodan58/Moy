/*
    module  : filetime.c
    version : 1.10
    date    : 03/15/21
*/
#ifndef FILETIME_C
#define FILETIME_C

#include <sys/stat.h>

/**
filetime  :  F  ->  T
T is the modification time of file F.
*/
PRIVATE void do_filetime(pEnv env)
{
    struct stat buf;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM("filetime");
    if (stat(env->stk->u.str, &buf) == -1)
	buf.st_mtime = 0;
    env->stk->op = INTEGER_;
    env->stk->u.num = buf.st_mtime;
}
#endif
