/*
    module  : fgets.c
    version : 1.8
    date    : 07/10/18
*/
#ifndef FGETS_X
#define FGETS_C

/**
fgets  :  S  ->  S L
L is the next available line (as a string) from stream S.
*/
PRIVATE void do_fgets(void)
{
    char *buf;
    size_t leng, size = INPLINEMAX;

#ifndef NCHECK
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
