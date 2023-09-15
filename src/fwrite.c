/*
    module  : fwrite.c
    version : 1.6
    date    : 09/15/23
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
    elem = lst_pop(env->stck);
    node = lst_back(env->stck);
    buf = GC_malloc_atomic(lst_size(elem.u.lis));
    for (i = 0, j = lst_size(elem.u.lis); i < j; i++) {
	temp = lst_at(elem.u.lis, j - i - 1);
	buf[i] = temp.u.num;
    }
    fwrite(buf, 1, lst_size(elem.u.lis), node.u.fil);
}
#endif
