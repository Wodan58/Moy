/*
    module  : fgets.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef FGETS_C
#define FGETS_C

/**
OK 1890  fgets  :  DAA	S  ->  S L
L is the next available line (as a string) from stream S.
*/
void fgets_(pEnv env)
{
    Node node;
    char *buf;
    size_t leng, size = INPLINEMAX;

    PARM(1, FGET);
    node = vec_back(env->stck);
    buf = GC_malloc_atomic(size);
    buf[leng = 0] = 0;
    while (fgets(buf + leng, size - leng, node.u.fil)) {
        if ((leng = strlen(buf)) > 0 && buf[leng - 1] == '\n')
            break;
        buf = GC_realloc(buf, size <<= 1);
    }
    node.u.str = buf;
    node.op = STRING_;
    vec_push(env->stck, node);
}
#endif
