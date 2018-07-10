/*
    module  : fwrite.c
    version : 1.9
    date    : 07/10/18
*/
#ifndef FWRITE_X
#define FWRITE_C

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
    COMPILE;
#endif
    TWOPARAMS("fwrite");
    LIST("fwrite");
    for (node = stk->u.lis, leng = 0; node; node = node->next, leng++)
	if (node->op != INTEGER_)
	    execerror("numeric list", "fwrite");
    buf = ck_malloc_sec(leng);
    for (node = stk->u.lis, i = 0; node; node = node->next, i++)
	buf[i] = node->u.num;
    POP(stk);
    FILE("fwrite");
    fwrite(buf, leng, 1, stk->u.fil);
}
#endif
