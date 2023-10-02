/*
    module  : cos.c
    version : 1.6
    date    : 10/02/23
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
    env->stck = pvec_pop(env->stck, &node);
    node.u.dbl = cos(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    env->stck = pvec_add(env->stck, node);
}
#endif
