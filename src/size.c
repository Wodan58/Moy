/*
    module  : size.c
    version : 1.7
    date    : 09/15/23
*/
#ifndef SIZE_C
#define SIZE_C

/**
OK 2080  size  :  DA	A  ->  I
Integer I is the number of elements of aggregate A.
*/
void size_(pEnv env)
{
    int i;
    Node node, temp;

    PARM(1, SIZE);
    node = lst_pop(env->stck);
    switch (node.op) {
    case LIST_:
	temp.u.num = lst_size(node.u.lis);
	break;
    case STRING_:
    case BIGNUM_:
	temp.u.num = strlen(node.u.str);
	break;
    case SET_:
	for (i = 0, temp.u.num = 0; i < SETSIZE; i++)
	    if (node.u.set & ((int64_t)1 << i))
		temp.u.num++;
	break;
    default:
	break;
    }
    temp.op = INTEGER_;
    lst_push(env->stck, temp);
}
#endif
