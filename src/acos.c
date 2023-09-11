/*
    module  : acos.c
    version : 1.4
    date    : 09/11/23
*/
#ifndef ACOS_C
#define ACOS_C

/**
OK 1490  acos  :  DA	F  ->  G
G is the arc cosine of F.
*/
void acos_(pEnv env)
{
#ifndef COMPILER
    Node node;

    PARM(1, UFLOAT);
    node = lst_pop(env->stck);
    node.u.dbl = acos(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    lst_push(env->stck, node);
#endif
}
#endif
