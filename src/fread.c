/*
    module  : fread.c
    version : 1.6
    date    : 09/11/23
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
#ifndef COMPILER
    int64_t count;
    Node node, elem;
    unsigned char *buf;

    PARM(2, FREAD);
    node = lst_pop(env->stck);
    count = node.u.num;
    node = lst_back(env->stck);
    buf = GC_malloc_atomic(count);
    count = fread(buf, 1, count, node.u.fil);
    lst_init(node.u.lis);
    elem.op = INTEGER_;
    for (--count; count >= 0; count--) {
	elem.u.num = buf[count];
	lst_push(node.u.lis, elem);
    }
    node.op = LIST_;
    lst_push(env->stck, node);
#endif
}
#endif
