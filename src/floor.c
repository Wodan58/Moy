/*
    module  : floor.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef FLOOR_C
#define FLOOR_C

/**
OK 1570  floor  :  DA	F  ->  G
G is the floor of F.
*/
void floor_(pEnv env)
{
    Node node;

    PARM(1, UFLOAT);
    env->stck = pvec_pop(env->stck, &node);
    node.u.dbl = floor(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    env->stck = pvec_add(env->stck, node);
}
#endif
