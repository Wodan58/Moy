/*
    module  : fread.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
fread  :  S I  ->  L
I bytes are read from the current position of stream S
and returned as a list of I integers.
*/
/* fread.c */
PRIVATE void fread_(void)
{
    int i;
    size_t count;
    Node *cur = 0;
    unsigned char *buf;

    TWOPARAMS("fread");
    INTEGER("fread");
    count = stk->u.num;
    POP(stk);
    FILE("fread");
    buf = GC_malloc(count);
    for (i = fread(buf, 1, count, stk->u.fil) - 1; i >= 0; i--)
	cur = newnode(INTEGER_, (void *)(long_t)buf[i], cur);
    PUSH(LIST_, cur);
}
