/*
    module  : fread.c
    version : 1.14
    date    : 03/15/21
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
    unsigned char *buf;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
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
