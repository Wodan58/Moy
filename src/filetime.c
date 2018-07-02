/*
    module  : filetime.c
    version : 1.6
    date    : 07/02/18
*/
#include <sys/stat.h>

/**
filetime  :  F  ->  T
T is the modification time of file F.
*/
PRIVATE void do_filetime(void)
{
    struct stat buf;

#ifndef NCHECK
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
