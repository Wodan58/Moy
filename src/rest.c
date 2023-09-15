/*
    module  : rest.c
    version : 1.7
    date    : 09/15/23
*/
#ifndef REST_C
#define REST_C

/**
OK 2040  rest  :  DA	A  ->  R
R is the non-empty aggregate A with its first member removed.
*/
void rest_(pEnv env)
{
    int i = 0;
    Node node, temp;

    PARM(1, FIRST);
    node = lst_pop(env->stck);
    switch (node.op) {
    case LIST_:
	lst_init(temp.u.lis);
	lst_shallow_copy(temp.u.lis, node.u.lis);
	(void)lst_pop(temp.u.lis);
	temp.op = LIST_;
	lst_push(env->stck, temp);
	break;

    case STRING_:
    case BIGNUM_:
    case USR_STRING_:
	node.u.str = GC_strdup(++node.u.str);  
	lst_push(env->stck, node);
	break;

    case SET_:
	while (!(node.u.set & ((int64_t)1 << i)))
	    i++;
	node.u.set &= ~((int64_t)1 << i);
	lst_push(env->stck, node);
	break;

    default:
	break;
    }
}
#endif
