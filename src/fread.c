/*
    module  : fread.c
    version : 1.15
    date    : 06/20/22
*/
#ifndef FREAD_C
#define FREAD_C

/**
fread  :  S I  ->  S L
I bytes are read from the current position of stream S
and returned as a list of I integers.
*/
PRIVATE void do_fread(pEnv env)
{
    int i, count;
    Node *cur = 0;
    unsigned char *volatile buf;

    COMPILE;
    TWOPARAMS("fread");
    INTEGER("fread");
    count = env->stk->u.num;
    POP(env->stk);
    FILE("fread");
    buf = GC_malloc_atomic(count);
    for (i = fread(buf, 1, count, env->stk->u.fil) - 1; i >= 0; i--)
	cur = INTEGER_NEWNODE(buf[i], cur);
    PUSH_PTR(LIST_, cur);
}
#endif
