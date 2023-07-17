/*
    module  : at.c
    version : 1.2
    date    : 07/17/23
*/
#ifndef AT_C
#define AT_C

/**
OK 2070  at  :  DDA	A I  ->  X
X (= A[I]) is the member of A at position I.
*/
void at_(pEnv env)
{
    int i, j;
    Node elem, aggr, node;

    PARM(2, AT);
    elem = vec_pop(env->stck);
    aggr = vec_pop(env->stck);
    switch (aggr.op) {
    case LIST_:
        node = vec_at(aggr.u.lis, vec_size(aggr.u.lis) - elem.u.num - 1);
        vec_push(env->stck, node);
        break;

    case STRING_:
        node.u.num = aggr.u.str[elem.u.num];
        node.op = CHAR_;
        vec_push(env->stck, node);
        break;

    case SET_:
        for (j = elem.u.num, i = 0; i < SETSIZE; i++)
            if (aggr.u.set & ((int64_t)1 << i)) {
                if (!j) {
                    node.u.num = i;
                    node.op = INTEGER_;
                    vec_push(env->stck, node);
                    break;
                }
                j--;
            }
    default:
        break;
    }
}
#endif
