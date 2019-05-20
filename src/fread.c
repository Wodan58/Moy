/*
    module  : fread.c
    version : 1.12
    date    : 05/18/19
*/
#ifndef FREAD_X
#define FREAD_C

#ifdef NEW_RUNTIME
void do_fread(void)
{
    int i, count;
    unsigned char *buf;
    code_t *root = 0, *cur;

    TRACE;
    count = do_pop();
    buf = ck_malloc_sec(count);
    for (i = fread(buf, 1, count, (FILE *)stk[-1]) - 1; i >= 0; i--) {
	cur = joy_code();
	cur->num = buf[i];
	cur->next = root;
	root = cur;
    }
    do_push((node_t)root);
}
#else
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

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS("fread");
    INTEGER("fread");
    count = stk->u.num;
    POP(stk);
    FILE("fread");
    buf = ck_malloc_sec(count);
    for (i = fread(buf, 1, count, stk->u.fil) - 1; i >= 0; i--)
	cur = newnode(INTEGER_, (void *)(long_t)buf[i], cur);
    PUSH(LIST_, cur);
}
#endif
#endif
