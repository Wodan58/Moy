/*
    module  : fread.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef FREAD_C
#define FREAD_C

/**
OK 1910  fread  :  DDAA	S I  ->  S L
I bytes are read from the current position of stream S
and returned as a list of I integers.
*/
void fread_(pEnv env)
{
    long count;
    Node node, elem;
    unsigned char *buf;

    PARM(2, FREAD);
    node = vec_pop(env->stck);
    count = node.u.num;
    node = vec_back(env->stck);
    buf = GC_malloc_atomic(count);
    count = fread(buf, 1, count, node.u.fil);
    vec_init(node.u.lis);
    elem.op = INTEGER_;
    for (--count; count >= 0; count--) {
        elem.u.num = buf[count];
        vec_push(node.u.lis, elem);
    }
    node.op = LIST_;
    vec_push(env->stck, node);
}
#endif
