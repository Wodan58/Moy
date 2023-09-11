/*
    module  : floor.c
    version : 1.4
    date    : 09/11/23
*/
#ifndef FLOOR_C
#define FLOOR_C

/**
OK 1570  floor  :  DA	F  ->  G
G is the floor of F.
*/
void floor_(pEnv env)
{
#ifndef COMPILER
    Node node;

    PARM(1, UFLOAT);
    node = lst_pop(env->stck);
    node.u.dbl = floor(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    lst_push(env->stck, node);
#endif
}
#endif
