/*
    module  : unswons.c
    version : 1.10
    date    : 03/05/24
*/
#ifndef UNSWONS_C
#define UNSWONS_C

/**
Q0  OK  2120  unswons  :  DAA  A  ->  R F
R and F are the rest and the first of non-empty aggregate A.
*/
void unswons_(pEnv env)
{
    int i = 0;
    Node node, temp;

    PARM(1, FIRST);
    env->stck = pvec_pop(env->stck, &node);
    switch (node.op) {
    case LIST_:
	temp.u.lis = pvec_init();
	pvec_shallow_copy(temp.u.lis, node.u.lis);
	temp.u.lis = pvec_pop(temp.u.lis, &node);
	temp.op = LIST_;
	env->stck = pvec_add(env->stck, temp);	/* push remainder */
	env->stck = pvec_add(env->stck, node);	/* push element */
	break;

    case STRING_:
    case BIGNUM_:
    case USR_STRING_:
	temp.u.num = *node.u.str++;
	node.u.str = GC_strdup(node.u.str);  
	env->stck = pvec_add(env->stck, node);
	temp.op = CHAR_;
	env->stck = pvec_add(env->stck, temp);
	break;

    case SET_:
	while (!(node.u.set & ((int64_t)1 << i)))
	    i++;
	temp.u.num = i;
	node.u.set &= ~((int64_t)1 << i);
	env->stck = pvec_add(env->stck, node);
	temp.op = INTEGER_;
	env->stck = pvec_add(env->stck, temp);
	break;
    }
}
#endif
