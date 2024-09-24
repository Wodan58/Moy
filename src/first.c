/*
    module  : first.c
    version : 1.11
    date    : 09/17/24
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
    node = vec_pop(env->stck);
    switch (node.op) {
    case LIST_:
	node = vec_back(node.u.lis);
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
    vec_push(env->stck, node);
}
#endif
