/*
    module  : fwrite.c
    version : 1.7
    date    : 10/02/23
*/
#ifndef FWRITE_C
#define FWRITE_C

/**
OK 1910  fwrite  :  D	S L  ->  S
A list of integers are written as bytes to the current position of stream S.
*/
void fwrite_(pEnv env)
{
    int i, j;
    unsigned char *buf;
    Node node, elem, temp;

    PARM(2, FWRITE);
    env->stck = pvec_pop(env->stck, &elem);
    node = pvec_lst(env->stck);
    j = pvec_cnt(elem.u.lis);
    buf = GC_malloc_atomic(j);
    for (i = 0; i < j; i++) {
	temp = pvec_nth(elem.u.lis, j - i - 1);
	buf[i] = temp.u.num;
    }
    fwrite(buf, 1, j, node.u.fil);
}
#endif
