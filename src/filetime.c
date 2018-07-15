/*
    module  : filetime.c
    version : 1.8
    date    : 07/15/18
*/
#ifndef FILETIME_X
#define FILETIME_C

#include <sys/stat.h>

#ifdef NEW_RUNTIME
void do_filetime(void)
{
    struct stat buf;

    TRACE;
    if (stat((char *)stk[-1], &buf) == -1)
	buf.st_mtime = 0;
    stk[-1] = buf.st_mtime;
}
#else
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
    if (OUTSIDE) {
	stk->op = INTEGER_;
	stk->u.num = buf.st_mtime;
    } else
	UNARY(INTEGER_NEWNODE, buf.st_mtime);
}
#endif
#endif
