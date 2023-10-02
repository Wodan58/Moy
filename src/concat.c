/*
    module  : concat.c
    version : 1.7
    date    : 10/02/23
*/
#ifndef CONCAT_C
#define CONCAT_C

/**
OK 2150  concat  :  DDA	S T  ->  U
Sequence U is the concatenation of sequences S and T.
*/
void concat_(pEnv env)
{
    int i, j;
    Node first, second, result;

    PARM(2, CONCAT);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    switch (first.op) {
    case LIST_:
	if (!pvec_cnt(first.u.lis))
	    result = second;
	else if (!pvec_cnt(second.u.lis))
	    result = first;
	else {
	    result.u.lis = pvec_init();
	    pvec_copy(result.u.lis, second.u.lis);
	    for (i = 0, j = pvec_cnt(first.u.lis); i < j; i++)
		result.u.lis = pvec_add(result.u.lis, pvec_nth(first.u.lis, i));
	}
	break;

    case STRING_:
    case BIGNUM_:
    case USR_STRING_:
	i = strlen(first.u.str);
	j = strlen(second.u.str);
	result.u.str = GC_malloc_atomic(i + j + 1);
	strcpy(result.u.str, first.u.str);
	strcpy(result.u.str + i, second.u.str);
	break;

    case SET_:
	result.u.set = first.u.set | second.u.set;
	break;

    default:
	result = first;
	break;
    }
    result.op = first.op;
    env->stck = pvec_add(env->stck, result);
}
#endif
