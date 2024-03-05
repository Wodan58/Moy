/*
    module  : first.c
    version : 1.10
    date    : 03/05/24
*/
#ifndef FIRST_C
#define FIRST_C

/**
Q0  OK  2030  first  :  DA  A  ->  F
F is the first member of the non-empty aggregate A.
*/
void first_(pEnv env)
{
    int i = 0;
    Node node;

    PARM(1, FIRST);
    env->stck = pvec_pop(env->stck, &node);
    switch (node.op) {
    case LIST_:
	node = pvec_lst(node.u.lis);
	break;

    case STRING_:
    case BIGNUM_:
    case USR_STRING_:
	node.u.num = *node.u.str;
	node.op = CHAR_;
	break;

    case SET_:
	while (!(node.u.set & ((int64_t)1 << i)))
	    i++;
	node.u.num = i;
	node.op = INTEGER_;
	break;
    }
    env->stck = pvec_add(env->stck, node);
}
#endif
