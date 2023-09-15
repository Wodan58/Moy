/*
    module  : floor.c
    version : 1.5
    date    : 09/15/23
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
    node = lst_pop(env->stck);
    node.u.dbl = floor(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    lst_push(env->stck, node);
}
#endif
