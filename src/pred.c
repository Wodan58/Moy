/*
    module  : pred.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef PRED_C
#define PRED_C

/**
OK 1790  pred  :  DA	M  ->  N
Numeric N is the predecessor of numeric M.
*/
void pred_(pEnv env)
{
    Node node;

    PARM(1, PREDSUCC);
    node = vec_pop(env->stck);
    node.u.num--;
    vec_push(env->stck, node);
}
#endif
