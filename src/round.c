/*
    module  : round.c
    version : 1.11
    date    : 09/17/24
*/
#ifndef ROUND_C
#define ROUND_C

/**
Q0  OK  3200  round  :  DA  F  ->  G
[EXT] G is F rounded to the nearest integer.
*/
void round_(pEnv env)
{
    Node node;

    PARM(1, UFLOAT);
    node = vec_pop(env->stck);
    node.u.dbl = round(node.op == FLOAT_ ? node.u.dbl : node.u.num);
    node.op = FLOAT_;
    vec_push(env->stck, node);
}
#endif
