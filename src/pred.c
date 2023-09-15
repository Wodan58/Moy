/*
    module  : pred.c
    version : 1.5
    date    : 09/15/23
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
    node = lst_pop(env->stck);
    node.u.num--;
    lst_push(env->stck, node);
}
#endif
