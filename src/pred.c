/*
    module  : pred.c
    version : 1.4
    date    : 09/11/23
*/
#ifndef PRED_C
#define PRED_C

/**
OK 1790  pred  :  DA	M  ->  N
Numeric N is the predecessor of numeric M.
*/
void pred_(pEnv env)
{
#ifndef COMPILER
    Node node;

    PARM(1, PREDSUCC);
    node = lst_pop(env->stck);
    node.u.num--;
    lst_push(env->stck, node);
#endif
}
#endif
