/*
    module  : rest.c
    version : 1.10
    date    : 03/05/24
*/
#ifndef REST_C
#define REST_C

/**
Q0  OK  2040  rest  :  DA  A  ->  R
R is the non-empty aggregate A with its first member removed.
*/
void rest_(pEnv env)
{
    int i = 0;
    Node node, temp;

    PARM(1, FIRST);
    env->stck = pvec_pop(env->stck, &node);
    switch (node.op) {
    case LIST_:
	temp.u.lis = pvec_init();
	pvec_shallow_copy(temp.u.lis, node.u.lis);
	node.u.lis = pvec_del(temp.u.lis);	/* remove first */
	break;

    case STRING_:
    case BIGNUM_:
    case USR_STRING_:
	node.u.str = GC_strdup(++node.u.str);  
	break;

    case SET_:
	while (!(node.u.set & ((int64_t)1 << i)))
	    i++;
	node.u.set &= ~((int64_t)1 << i);
	break;
    }
    env->stck = pvec_add(env->stck, node);	/* push remainder */
}
#endif
