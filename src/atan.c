/*
    module  : atan.c
    version : 1.4
    date    : 09/11/23
*/
#ifndef ATAN_C
#define ATAN_C

/**
OK 1510  atan  :  DA	F  ->  G
G is the arc tangent of F.
*/
void atan_(pEnv env)
{
#ifndef COMPILER
    Node node;

    PARM(1, UFLOAT);
    node = lst_pop(env->stck);
    node.u.dbl = atan(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    lst_push(env->stck, node);
#endif
}
#endif
