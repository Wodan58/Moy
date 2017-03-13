/*
    module  : fread.c
    version : 1.5
    date    : 03/12/17
*/
#include "runtime.h"

/*
fread  :  S I  ->  L
I bytes are read from the current position of stream S
and returned as a list of I integers.
*/
PRIVATE void do_fread(void)
{
    char *buf;
    int i, count;
    Node *cur = 0;

#ifndef NCHECK
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
