/*
    module  : size.c
    version : 1.8
    date    : 10/02/23
*/
#ifndef SIZE_C
#define SIZE_C

/**
OK 2080  size  :  DA	A  ->  I
Integer I is the number of elements of aggregate A.
*/
void size_(pEnv env)
{
    int64_t i, j;
    Node node, temp;

    PARM(1, SIZE);
    env->stck = pvec_pop(env->stck, &node);
    switch (node.op) {
    case LIST_:
	temp.u.num = pvec_cnt(node.u.lis);
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
    default:
	break;
    }
    temp.op = INTEGER_;
    env->stck = pvec_add(env->stck, temp);
}
#endif
