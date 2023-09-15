/*
    module  : equal.c
    version : 1.6
    date    : 09/15/23
*/
#ifndef EQUAL_C
#define EQUAL_C

#include "compare.h"

/**
OK 2280  equal  :  DDA	T U  ->  B
(Recursively) tests whether trees T and U are identical.
*/
PRIVATE int compatible(int first, int second)
{
    switch (first) {
    case BOOLEAN_:
    case CHAR_:
    case INTEGER_:
    case SET_:
    case FLOAT_:
	switch (second) {
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	case SET_:
	case FLOAT_:
	case BIGNUM_:
	    return 1;

	default:
	    return 0;
	}
	break;

    case USR_:
    case ANON_FUNCT_:
    case STRING_:
    case USR_STRING_:
	switch (second) {
	case USR_:
	case ANON_FUNCT_:
	case STRING_:
	case BIGNUM_:
	case USR_STRING_:
	    return 1;

	default:
	    return 0;
	}
	break;

    case BIGNUM_:
	switch (second) {
	case USR_:
	case ANON_FUNCT_:
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	case SET_:
	case STRING_:
	case FLOAT_:
	case BIGNUM_:
	case USR_STRING_:
	    return 1;

	default:
	    return 0;
	}
	break;

    default:
	break;
    }
    return first == second;
}

PRIVATE int is_equal(pEnv env, Node first, Node second)
{
    int i, j;
    Node temp;
    NodeList *stackf = 0, *stacks = 0;

    if (!compatible(first.op, second.op))
	return 0; /* unequal */
    if (first.op != LIST_)
	return Compare(env, first, second) == 0;
    if ((j = lst_size(first.u.lis)) != lst_size(second.u.lis))
	return 0; /* unequal */
    if (j) {
	lst_init(stackf);
	lst_init(stacks);
    }
    for (i = 0; i < j; i++) {
	temp = lst_at(first.u.lis, i);
	lst_push(stackf, temp);
	temp = lst_at(second.u.lis, i);
	lst_push(stacks, temp);
    }
    while (lst_size(stackf)) {
	first = lst_pop(stackf);
	second = lst_pop(stacks);
	if (!compatible(first.op, second.op))
	    return 0; /* unequal */
	if (first.op != LIST_) {
	    if (Compare(env, first, second))
		return 0; /* unequal */
	} else {
	    if ((j = lst_size(first.u.lis)) != lst_size(second.u.lis))
		return 0; /* unequal */
	    for (i = 0; i < j; i++) {
		temp = lst_at(first.u.lis, i);
		lst_push(stackf, temp);
		temp = lst_at(second.u.lis, i);
		lst_push(stacks, temp);
	    }	    
	}
    }
    return 1; /* equal */
}

void equal_(pEnv env)
{
    Node first, second;

    PARM(2, ANYTYPE);
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
    first.u.num = is_equal(env, first, second);
    first.op = BOOLEAN_;
    lst_push(env->stck, first);
}
#endif
