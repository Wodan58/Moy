/*
    module  : filetime.c
    version : 1.1
    date    : 05/06/16
*/
#include "interp.h"
#include <sys/stat.h>

/*
filetime  :  F  ->  T
T is the modification time of file F.
*/
/* filetime.c */
PRIVATE void filetime_(void)
{
    struct stat buf;

    ONEPARAM("filetime");
    stat(stk->u.str, &buf);
    if (OUTSIDE) {
	stk->op = INTEGER_;
	stk->u.num = buf.st_mtime;
    } else
	UNARY(INTEGER_NEWNODE, buf.st_mtime);
}
