/*
    module  : filetime.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"
#include <sys/stat.h>

/*
filetime  :  F  ->  T
T is the modification time of file F.
*/
PRIVATE void do_filetime(void)
{
    struct stat buf;

#ifndef NCHECK
    COMPILE;
    ONEPARAM("filetime");
#endif
    stat(stk->u.str, &buf);
    if (OUTSIDE) {
	stk->op = INTEGER_;
	stk->u.num = buf.st_mtime;
    } else
	UNARY(INTEGER_NEWNODE, buf.st_mtime);
}
