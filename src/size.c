/*
    module  : size.c
    version : 1.12
    date    : 09/17/24
*/
#ifndef SIZE_C
#define SIZE_C

/**
Q0  OK  2080  size  :  DA  A  ->  I
Integer I is the number of elements of aggregate A.
*/
void size_(pEnv env)
{
    int64_t i, j;
    Node node, temp;

    PARM(1, SIZE_);
    node = vec_pop(env->stck);
    switch (node.op) {
    case LIST_:
	temp.u.num = vec_size(node.u.lis);
	break;
    case STRING_:
    case BIGNUM_:
	temp.u.num = strlen(node.u.str);
	break;
    case SET_:
	for (temp.u.num = 0, j = 1, i = 0; i < SETSIZE; i++, j <<= 1)
	    if (node.u.set & j)
		temp.u.num++;
	break;
    }
    temp.op = INTEGER_;
    vec_push(env->stck, temp);
}
#endif
