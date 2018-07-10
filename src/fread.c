/*
    module  : fread.c
    version : 1.10
    date    : 07/10/18
*/
#ifndef FREAD_X
#define FREAD_C

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
    COMPILE;
#endif
    TWOPARAMS("fread");
    INTEGER("fread");
    count = stk->u.num;
    POP(stk);
    FILE("fread");
    buf = ck_malloc_sec(count);
    for (i = fread(buf, 1, count, stk->u.fil) - 1; i >= 0; i--)
	cur = heapnode(INTEGER_, (void *)(long_t)buf[i], cur);
    PUSH(LIST_, cur);
}
#endif
