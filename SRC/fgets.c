/*
    module  : fgets.c
    version : 1.4
    date    : 03/12/17
*/
#include "runtime.h"

/*
fgets  :  S  ->  S L
L is the next available line (as a string) from stream S.
*/
PRIVATE void do_fgets(void)
{
    char *buf;
    size_t leng, size = INPLINEMAX;

#ifndef NCHECK
    COMPILE;
    ONEPARAM("fgets");
    FILE("fgets");
#endif
    buf = GC_malloc_atomic(size);
    buf[leng = 0] = 0;
    while (fgets(buf + leng, size - leng, stk->u.fil)) {
	if ((leng = strlen(buf)) > 0 && buf[leng - 1] == '\n')
	    break;
	buf = GC_realloc(buf, size <<= 1);
    }
    PUSH(STRING_, buf);
}
