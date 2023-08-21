/*
    module  : uncons.c
    version : 1.3
    date    : 08/21/23
*/
#ifndef UNCONS_C
#define UNCONS_C

/**
OK 2120  uncons  :  DAA	A  ->  F R
F and R are the first and the rest of non-empty aggregate A.
*/
void uncons_(pEnv env)
{
    int i = 0;
    Node node, temp;

    PARM(1, FIRST);
    node = vec_pop(env->stck);
    switch (node.op) {
    case LIST_:
        vec_init(temp.u.lis);
        vec_shallow_copy(temp.u.lis, node.u.lis);
        node = vec_pop(temp.u.lis);
        vec_push(env->stck, node);
        temp.op = LIST_;
        vec_push(env->stck, temp);
        break;

    case STRING_:
    case BIGNUM_:
        temp.u.num = *node.u.str++;
        temp.op = CHAR_;
        vec_push(env->stck, temp);
        node.u.str = GC_strdup(node.u.str);  
        vec_push(env->stck, node);
        break;

    case SET_:
        while (!(node.u.set & ((int64_t)1 << i)))
            i++;
        temp.u.num = i;
        temp.op = INTEGER_;
        vec_push(env->stck, temp);
        node.u.set &= ~((int64_t)1 << i);
        vec_push(env->stck, node);
    default:
        break;
    }
}
#endif
