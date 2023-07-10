/*
    module  : cons.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef CONS_C
#define CONS_C

/**
OK 2020  cons  :  DDA	X A  ->  B
Aggregate B is A with a new member X (first member for sequences).
*/
void cons_(pEnv env)
{
    Node elem, aggr, node;

    PARM(2, CONS);
    aggr = vec_pop(env->stck);
    elem = vec_pop(env->stck);
    switch (aggr.op) {
    case LIST_:
        vec_init(node.u.lis);
        if (vec_size(aggr.u.lis))
            vec_shallow_copy_take_ownership(node.u.lis, aggr.u.lis);
        vec_push(node.u.lis, elem);
        break;

    case STRING_:
        node.u.str = GC_malloc_atomic(strlen(aggr.u.str) + 2);
        node.u.str[0] = elem.u.num;
        strcpy(&node.u.str[1], aggr.u.str);
        break;

    case SET_:
        node.u.set = aggr.u.set | ((long)1 << elem.u.num);
    default:
        break;
    }
    node.op = aggr.op;
    vec_push(env->stck, node);
}
#endif
