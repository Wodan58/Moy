/*
    module  : fgets.c
    version : 1.10
    date    : 03/28/20
*/
#ifndef FGETS_C
#define FGETS_C

/**
fgets  :  S  ->  S L
L is the next available line (as a string) from stream S.
*/
PRIVATE void do_fgets(void)
{
    char *buf;
    size_t leng, size = INPLINEMAX;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM("fgets");
    FILE("fgets");
    buf = ck_malloc_sec(size);
    buf[leng = 0] = 0;
    while (fgets(buf + leng, size - leng, stk->u.fil)) {
	if ((leng = strlen(buf)) > 0 && buf[leng - 1] == '\n')
	    break;
	buf = ck_realloc(buf, size <<= 1);
    }
    PUSH(STRING_, buf);
}
#endif
