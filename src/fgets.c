/*
    module  : fgets.c
    version : 1.6
    date    : 06/25/18
*/
#include "runtime.h"

/**
fgets  :  S  ->  S L
L is the next available line (as a string) from stream S.
*/
PRIVATE void do_fgets(void)
{
    char *buf;
    size_t leng, size = INPLINEMAX;

#ifndef NCHECK
    if (optimizing)
	add_history(STRING_);
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
