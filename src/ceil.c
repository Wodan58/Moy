/*
    module  : ceil.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef CEIL_C
#define CEIL_C

/**
OK 1530  ceil  :  DA	F  ->  G
G is the float ceiling of F.
*/
void ceil_(pEnv env)
{
    Node node;

    PARM(1, UFLOAT);
    node = vec_pop(env->stck);
    node.u.dbl = ceil(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    vec_push(env->stck, node);
}
#endif
