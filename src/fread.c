/*
    module  : fread.c
    version : 1.8
    date    : 10/02/23
*/
#ifndef FREAD_C
#define FREAD_C

/**
OK 1900  fread  :  DA	S I  ->  S L
I bytes are read from the current position of stream S
and returned as a list of I integers.
*/
void fread_(pEnv env)
{
    int64_t count;
    Node node, elem;
    unsigned char *buf;

    PARM(2, FREAD);
    env->stck = pvec_pop(env->stck, &node);
    count = node.u.num;
    node = pvec_lst(env->stck);
    buf = GC_malloc_atomic(count);
    count = fread(buf, 1, count, node.u.fil);
    node.u.lis = pvec_init();
    elem.op = INTEGER_;
    for (--count; count >= 0; count--) {
	elem.u.num = buf[count];
	node.u.lis = pvec_add(node.u.lis, elem);
    }
    node.op = LIST_;
    env->stck = pvec_add(env->stck, node);
}
#endif
