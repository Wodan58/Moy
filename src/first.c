/*
    module  : first.c
    version : 1.6
    date    : 09/11/23
*/
#ifndef FIRST_C
#define FIRST_C

/**
OK 2030  first  :  DA	A  ->  F
F is the first member of the non-empty aggregate A.
*/
void first_(pEnv env)
{
#ifndef COMPILER
    int i = 0;
    Node node, temp;

    PARM(1, FIRST);
    node = lst_pop(env->stck);
    switch (node.op) {
    case LIST_:
	temp = lst_back(node.u.lis);
	lst_push(env->stck, temp);
	break;

    case STRING_:
    case BIGNUM_:
	temp.u.num = *node.u.str;
	temp.op = CHAR_;
	lst_push(env->stck, temp);
	break;

    case SET_:
	while (!(node.u.set & ((int64_t)1 << i)))
	    i++;
	temp.u.num = i;
	temp.op = INTEGER_;
	lst_push(env->stck, temp);
    default:
	break;
    }
#endif
}
#endif
