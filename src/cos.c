/*
    module  : cos.c
    version : 1.5
    date    : 09/15/23
*/
#ifndef COS_C
#define COS_C

/**
OK 1540  cos  :  DA	F  ->  G
G is the cosine of F.
*/
void cos_(pEnv env)
{
    Node node;

    PARM(1, UFLOAT);
    node = lst_pop(env->stck);
    node.u.dbl = cos(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    lst_push(env->stck, node);
}
#endif
