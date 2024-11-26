/*
    module  : rest.c
    version : 1.12
    date    : 11/20/24
*/
#ifndef REST_C
#define REST_C

/**
Q0  OK  2040  rest  :  DA  A  ->  R
R is the non-empty aggregate A with its first member removed.
*/
void rest_(pEnv env)
{
    int i = 0;
    Node aggr, temp;

    PARM(1, FIRST);
    aggr = vec_pop(env->stck);
    switch (aggr.op) {
    case LIST_:
        vec_shallow_copy(temp.u.lis, aggr.u.lis);
        vec_reduce(temp.u.lis, 1);
	aggr.u.lis = temp.u.lis;
	break;

    case STRING_:
    case BIGNUM_:
    case USR_STRING_:
	aggr.u.str = GC_strdup(++aggr.u.str);  
	break;

    case SET_:
	while (!(aggr.u.set & ((int64_t)1 << i)))
	    i++;
	aggr.u.set &= ~((int64_t)1 << i);
	break;
    }
    vec_push(env->stck, aggr);
}
#endif
