/*
    module  : tan.c
    version : 1.5
    date    : 09/15/23
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
    node = lst_pop(env->stck);
    node.u.dbl = tan(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    lst_push(env->stck, node);
}
#endif
