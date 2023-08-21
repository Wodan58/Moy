/*
    module  : step.c
    version : 1.3
    date    : 08/21/23
*/
#ifndef STEP_C
#define STEP_C

/**
OK 2790  step  :  DDU	A [P]  ->  ...
Sequentially putting members of aggregate A onto stack,
executes P for each member of A.
*/
void step_(pEnv env)
{
    int i, j;
    Node aggr, list, node;

    PARM(2, STEP);
    list = vec_pop(env->stck);
    aggr = vec_pop(env->stck);
    switch (aggr.op) {
    case LIST_:
        for (i = 0, j = vec_size(aggr.u.lis); i < j; i++) {
            prog(env, list.u.lis);
            node = vec_at(aggr.u.lis, i);
            prime(env, node);
        }
        break;

    case STRING_:
    case BIGNUM_:
        node.op = CHAR_;
        for (i = strlen(aggr.u.str) - 1; i >= 0; i--) {
            prog(env, list.u.lis);
            node.u.num = aggr.u.str[i];
            vec_push(env->prog, node);
        }
        break;

    case SET_:
        node.op = INTEGER_;
        for (i = SETSIZE - 1; i >= 0; i--)
            if (aggr.u.set & ((int64_t)1 << i)) {
                prog(env, list.u.lis);
                node.u.num = i;
                vec_push(env->prog, node);
            }
    default:
        break;
    }
}
#endif
