/*
    module  : ceil.c
    version : 1.4
    date    : 09/11/23
*/
#ifndef CEIL_C
#define CEIL_C

/**
OK 1530  ceil  :  DA	F  ->  G
G is the float ceiling of F.
*/
void ceil_(pEnv env)
{
#ifndef COMPILER
    Node node;

    PARM(1, UFLOAT);
    node = lst_pop(env->stck);
    node.u.dbl = ceil(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    lst_push(env->stck, node);
#endif
}
#endif
