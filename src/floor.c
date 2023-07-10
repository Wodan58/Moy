/*
    module  : floor.c
    version : 1.1
    date    : 07/10/23
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
    node = vec_pop(env->stck);
    node.u.dbl = floor(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    vec_push(env->stck, node);
}
#endif
