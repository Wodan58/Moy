/*
    module  : filetime.c
    version : 1.9
    date    : 03/28/20
*/
#ifndef FILETIME_C
#define FILETIME_C

#include <sys/stat.h>

/**
filetime  :  F  ->  T
T is the modification time of file F.
*/
PRIVATE void do_filetime(void)
{
    struct stat buf;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM("filetime");
    if (stat(stk->u.str, &buf) == -1)
	buf.st_mtime = 0;
    stk->op = INTEGER_;
    stk->u.num = buf.st_mtime;
}
#endif
