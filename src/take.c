/*
    module  : take.c
    version : 1.2
    date    : 08/21/23
*/
#ifndef TAKE_C
#define TAKE_C

/**
OK 2150  take  :  DDA	A N  ->  B
Aggregate B is the result of retaining just the first N elements of A.
*/
void take_(pEnv env)
{
    int i, j;
    Node elem, aggr, node;

    PARM(2, TAKE);
    elem = vec_pop(env->stck);
    aggr = vec_pop(env->stck);
    switch (aggr.op) {
    case LIST_:
        j = vec_size(aggr.u.lis);
        if (elem.u.num >= j)
            node = aggr;
        else {
            vec_init(node.u.lis);
            for (i = j - elem.u.num; i < j; i++)
                vec_push(node.u.lis, vec_at(aggr.u.lis, i));
            node.op = LIST_;
        }
        break;

    case STRING_:
    case BIGNUM_:
        j = strlen(aggr.u.str);
        if (elem.u.num >= j)
            node = aggr;
        else {
            node.u.str = GC_malloc_atomic(elem.u.num + 1);
            strncpy(node.u.str, aggr.u.str, elem.u.num);
            node.u.str[elem.u.num] = 0;
            node.op = STRING_;
        }
        break;

    case SET_:
        node.u.set = 0;
        for (i = 0, j = 1; i < SETSIZE && elem.u.num; i++, j <<= 1)
            if (aggr.u.set & j) {
                node.u.set |= j;
                elem.u.num--;
            }
        node.op = SET_;
    default:
        break;
    }
    vec_push(env->stck, node);
}
#endif
