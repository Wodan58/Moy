/*
    module  : uncons.c
    version : 1.7
    date    : 09/15/23
*/
#ifndef UNCONS_C
#define UNCONS_C

/**
OK 2110  uncons  :  DAA	A  ->  F R
F and R are the first and the rest of non-empty aggregate A.
*/
void uncons_(pEnv env)
{
    int i = 0;
    Node node, temp;

    PARM(1, FIRST);
    node = lst_pop(env->stck);
    switch (node.op) {
    case LIST_:
	lst_init(temp.u.lis);
	lst_shallow_copy(temp.u.lis, node.u.lis);
	node = lst_pop(temp.u.lis);
	lst_push(env->stck, node);
	temp.op = LIST_;
	lst_push(env->stck, temp);
	break;

    case STRING_:
    case BIGNUM_:
    case USR_STRING_:
	temp.u.num = *node.u.str++;
	temp.op = CHAR_;
	lst_push(env->stck, temp);
	node.u.str = GC_strdup(node.u.str);  
	lst_push(env->stck, node);
	break;

    case SET_:
	while (!(node.u.set & ((int64_t)1 << i)))
	    i++;
	temp.u.num = i;
	temp.op = INTEGER_;
	lst_push(env->stck, temp);
	node.u.set &= ~((int64_t)1 << i);
	lst_push(env->stck, node);
	break;

    default:
	break;
    }
}
#endif
