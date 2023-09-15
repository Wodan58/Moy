/*
    module  : acos.c
    version : 1.5
    date    : 09/15/23
*/
#ifndef ACOS_C
#define ACOS_C

/**
OK 1490  acos  :  DA	F  ->  G
G is the arc cosine of F.
*/
void acos_(pEnv env)
{
    Node node;

    PARM(1, UFLOAT);
    node = lst_pop(env->stck);
    node.u.dbl = acos(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    lst_push(env->stck, node);
}
#endif
