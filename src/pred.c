/*
    module  : pred.c
    version : 1.7
    date    : 03/05/24
*/
#ifndef PRED_C
#define PRED_C

/**
Q0  OK  1790  pred  :  DA  M  ->  N
Numeric N is the predecessor of numeric M.
*/
void pred_(pEnv env)
{
    Node node;

    PARM(1, PREDSUCC);
    env->stck = pvec_pop(env->stck, &node);
    node.u.num--;
    env->stck = pvec_add(env->stck, node);
}
#endif
