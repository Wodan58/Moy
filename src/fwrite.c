/*
    module  : fwrite.c
    version : 1.7
    date    : 06/25/18
*/
#include "runtime.h"

/**
fwrite  :  S L  ->  S
A list of integers are written as bytes to the current position of stream S.
*/
PRIVATE void do_fwrite(void)
{
    Node *node;
    int i, leng;
    unsigned char *buf;

#ifndef NCHECK
    if (optimizing)
	del_history(1);
    COMPILE;
    TWOPARAMS("fwrite");
    LIST("fwrite");
#endif
    for (node = stk->u.lis, leng = 0; node; node = node->next, leng++)
#ifndef NCHECK
	if (node->op != INTEGER_)
	    execerror("numeric list", "fwrite");
#else
	;
#endif
    buf = GC_malloc_atomic(leng);
    for (node = stk->u.lis, i = 0; node; node = node->next, i++)
	buf[i] = node->u.num;
    POP(stk);
#ifndef NCHECK
    FILE("fwrite");
#endif
    fwrite(buf, leng, 1, stk->u.fil);
}
