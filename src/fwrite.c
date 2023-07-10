/*
    module  : fwrite.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef FWRITE_C
#define FWRITE_C

/**
OK 1920  fwrite  :  DDA	S L  ->  S
A list of integers are written as bytes to the current position of stream S.
*/
void fwrite_(pEnv env)
{
    int i, j;
    unsigned char *buf;
    Node node, elem, temp;

    PARM(2, FWRITE);
    elem = vec_pop(env->stck);
    node = vec_back(env->stck);
    buf = GC_malloc_atomic(vec_size(elem.u.lis));
    for (i = 0, j = vec_size(elem.u.lis); i < j; i++) {
        temp = vec_at(elem.u.lis, j - i - 1);
        buf[i] = temp.u.num;
    }
    fwrite(buf, 1, vec_size(elem.u.lis), node.u.fil);
}
#endif
