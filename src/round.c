/*
    module  : round.c
    version : 1.3
    date    : 08/26/23
*/
#ifndef ROUND_C
#define ROUND_C

/**
OK 1693  round  :  DA	F  ->  G
G is F rounded to the nearest integer.
*/
double round2(double num)
{
    if (num < 0)
        return -floor(-num + 0.5);
    return floor(num + 0.5);
}

void round_(pEnv env)
{
    Node node;

    PARM(1, UFLOAT);
    node = lst_pop(env->stck);
    node.u.dbl = round2(node.op == FLOAT_ ? node.u.dbl : node.u.num);
    node.op = FLOAT_;
    lst_push(env->stck, node);
}
#endif
