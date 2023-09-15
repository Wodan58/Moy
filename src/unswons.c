/*
    module  : unswons.c
    version : 1.7
    date    : 09/15/23
*/
#ifndef UNSWONS_C
#define UNSWONS_C

/**
OK 2120  unswons  :  DAA	A  ->  R F
R and F are the rest and the first of non-empty aggregate A.
*/
void unswons_(pEnv env)
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
	temp.op = LIST_;
	lst_push(env->stck, temp);
	lst_push(env->stck, node);
	break;

    case STRING_:
    case BIGNUM_:
    case USR_STRING_:
	temp.u.num = *node.u.str++;
	node.u.str = GC_strdup(node.u.str);  
	lst_push(env->stck, node);
	temp.op = CHAR_;
	lst_push(env->stck, temp);
	break;

    case SET_:
	while (!(node.u.set & ((int64_t)1 << i)))
	    i++;
	temp.u.num = i;
	node.u.set &= ~((int64_t)1 << i);
	lst_push(env->stck, node);
	temp.op = INTEGER_;
	lst_push(env->stck, temp);
	break;

    default:
	break;
    }
}
#endif
