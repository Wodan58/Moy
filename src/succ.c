/*
    module  : succ.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef SUCC_C
#define SUCC_C

/**
OK 1800  succ  :  DA	M  ->  N
Numeric N is the successor of numeric M.
*/
void succ_(pEnv env)
{
    Node node;

    PARM(1, PREDSUCC);
    node = vec_pop(env->stck);
    node.u.num++;
    vec_push(env->stck, node);
}
#endif
