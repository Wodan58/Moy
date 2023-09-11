/*
    module  : succ.c
    version : 1.4
    date    : 09/11/23
*/
#ifndef SUCC_C
#define SUCC_C

/**
OK 1800  succ  :  DA	M  ->  N
Numeric N is the successor of numeric M.
*/
void succ_(pEnv env)
{
#ifndef COMPILER
    Node node;

    PARM(1, PREDSUCC);
    node = lst_pop(env->stck);
    node.u.num++;
    lst_push(env->stck, node);
#endif
}
#endif
