/*
    module  : fgets.c
    version : 1.12
    date    : 06/20/22
*/
#ifndef FGETS_C
#define FGETS_C

/**
fgets  :  S  ->  S L
L is the next available line (as a string) from stream S.
*/
PRIVATE void do_fgets(pEnv env)
{
    char *buf;
    size_t leng, size = INPLINEMAX;

    COMPILE;
    ONEPARAM("fgets");
    FILE("fgets");
    buf = GC_malloc_atomic(size);
    buf[leng = 0] = 0;
    while (fgets(buf + leng, size - leng, env->stk->u.fil)) {
	if ((leng = strlen(buf)) > 0 && buf[leng - 1] == '\n')
	    break;
	buf = GC_realloc(buf, size <<= 1);
    }
    PUSH_PTR(STRING_, buf);
}
#endif
