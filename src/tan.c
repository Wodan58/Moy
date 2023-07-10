/*
    module  : tan.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef TAN_C
#define TAN_C

/**
OK 1670  tan  :  DA	F  ->  G
G is the tangent of F.
*/
void tan_(pEnv env)
{
    Node node;

    PARM(1, UFLOAT);
    node = vec_pop(env->stck);
    node.u.dbl = tan(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    vec_push(env->stck, node);
}
#endif
