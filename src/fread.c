/*
    module  : fread.c
    version : 1.8
    date    : 06/25/18
*/
#include "runtime.h"

/**
fread  :  S I  ->  S L
I bytes are read from the current position of stream S
and returned as a list of I integers.
*/
PRIVATE void do_fread(void)
{
    int i, count;
    Node *cur = 0;
    unsigned char *buf;

#ifndef NCHECK
    if (optimizing)
	chg_history2(LIST_, INTEGER_);
    COMPILE;
    TWOPARAMS("fread");
    INTEGER("fread");
#endif
    count = stk->u.num;
    POP(stk);
#ifndef NCHECK
    FILE("fread");
#endif
    buf = GC_malloc_atomic(count);
    for (i = fread(buf, 1, count, stk->u.fil) - 1; i >= 0; i--)
	cur = heapnode(INTEGER_, (void *)(long_t)buf[i], cur);
    PUSH(LIST_, cur);
}
