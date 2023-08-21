/*
    module  : has.c
    version : 1.3
    date    : 08/21/23
*/
#ifndef HAS_C
#define HAS_C

/**
OK 2300  has  :  DDA	A X  ->  B
Tests whether aggregate A has X as a member.
*/
void has_(pEnv env)
{
    int i, found = 0;
    Node aggr, elem, node;

    PARM(2, HAS);
    elem = vec_pop(env->stck);
    aggr = vec_pop(env->stck);
    switch (aggr.op) {
    case LIST_:
        for (i = vec_size(aggr.u.lis) - 1; i >= 0; i--) {
            node = vec_at(aggr.u.lis, i);
            if (!Compare(env, node, elem)) {
                found = 1;
                break;
            }
        }
        break;
    case STRING_:
    case BIGNUM_:
        for (i = strlen(aggr.u.str) - 1; i >= 0; i--)
            if (aggr.u.str[i] == elem.u.num) {
                found = 1;
                break;
            }
        break;
    case SET_:
        found = (aggr.u.set & ((int64_t)1 << elem.u.num)) > 0;
    default:
        break;
    }
    node.u.num = found;
    node.op = BOOLEAN_;
    vec_push(env->stck, node);
}
#endif
