/*
    module  : concat.c
    version : 1.6
    date    : 09/15/23
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
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
    switch (first.op) {
    case LIST_:
	if (!lst_size(first.u.lis))
	    result = second;
	else if (!lst_size(second.u.lis))
	    result = first;
	else {
	    lst_init(result.u.lis);
	    lst_copy(result.u.lis, second.u.lis);
	    for (i = 0, j = lst_size(first.u.lis); i < j; i++)
		lst_push(result.u.lis, lst_at(first.u.lis, i));
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
    lst_push(env->stck, result);
}
#endif
