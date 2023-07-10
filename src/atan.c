/*
    module  : atan.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef ATAN_C
#define ATAN_C

/**
OK 1510  atan  :  DA	F  ->  G
G is the arc tangent of F.
*/
void atan_(pEnv env)
{
    Node node;

    PARM(1, UFLOAT);
    node = vec_pop(env->stck);
    node.u.dbl = atan(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    vec_push(env->stck, node);
}
#endif
