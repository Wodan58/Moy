/*
    module  : filetime.c
    version : 1.5
    date    : 06/25/18
*/
#include "runtime.h"
#include <sys/stat.h>

/**
filetime  :  F  ->  T
T is the modification time of file F.
*/
PRIVATE void do_filetime(void)
{
    struct stat buf;

#ifndef NCHECK
    if (optimizing)
	chg_history(INTEGER_);
    COMPILE;
    ONEPARAM("filetime");
#endif
    if (stat(stk->u.str, &buf) == -1)
	buf.st_mtime = 0;
    if (OUTSIDE) {
	stk->op = INTEGER_;
	stk->u.num = buf.st_mtime;
    } else
	UNARY(INTEGER_NEWNODE, buf.st_mtime);
}
