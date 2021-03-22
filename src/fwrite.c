/*
    module  : fwrite.c
    version : 1.12
    date    : 03/15/21
*/
#ifndef FWRITE_C
#define FWRITE_C

/**
fwrite  :  S L  ->  S
A list of integers are written as bytes to the current position of stream S.
*/
PRIVATE void do_fwrite(pEnv env)
{
    Node *node;
    int i, leng;
    unsigned char *buf;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS("fwrite");
    LIST("fwrite");
    for (node = env->stk->u.lis, leng = 0; node; node = node->next, leng++) {
#ifndef NCHECK
	if (node->op != INTEGER_)
	    execerror("numeric list", "fwrite");
#endif
    }
    buf = GC_malloc_atomic(leng);
    for (node = env->stk->u.lis, i = 0; node; node = node->next, i++)
	buf[i] = node->u.num;
    POP(env->stk);
    FILE("fwrite");
    fwrite(buf, leng, 1, env->stk->u.fil);
}
#endif
