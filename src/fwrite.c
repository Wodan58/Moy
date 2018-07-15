/*
    module  : fwrite.c
    version : 1.10
    date    : 07/15/18
*/
#ifndef FWRITE_X
#define FWRITE_C

#ifdef NEW_RUNTIME
void do_fwrite(void)
{
    code_t *cur;
    size_t i, leng;
    unsigned char *buf;

    TRACE;
    cur = (code_t *)do_pop();
    leng = joy_leng(cur);
    buf = ck_malloc_sec(leng);
    for (i = 0; cur; cur = cur->next)
	buf[i++] = cur->num;
    fwrite(buf, leng, 1, (FILE *)stk[-1]);
}
#else
/**
fwrite  :  S L  ->  S
A list of integers are written as bytes to the current position of stream S.
*/
PRIVATE void do_fwrite(void)
{
    Node *node;
    int i, leng;
    unsigned char *buf;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS("fwrite");
    LIST("fwrite");
    for (node = stk->u.lis, leng = 0; node; node = node->next, leng++) {
#ifndef NCHECK
	if (node->op != INTEGER_)
	    execerror("numeric list", "fwrite");
#endif
    }
    buf = ck_malloc_sec(leng);
    for (node = stk->u.lis, i = 0; node; node = node->next, i++)
	buf[i] = node->u.num;
    POP(stk);
    FILE("fwrite");
    fwrite(buf, leng, 1, stk->u.fil);
}
#endif
#endif
