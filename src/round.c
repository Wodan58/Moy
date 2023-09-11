/*
    module  : round.c
    version : 1.5
    date    : 09/11/23
*/
#ifndef ROUND_C
#define ROUND_C

/**
OK 3230  round  :  DA	F  ->  G
[EXT] G is F rounded to the nearest integer.
*/
#ifndef COMPILER
double round2(double num)
{
    if (num < 0)
	return -floor(-num + 0.5);
    return floor(num + 0.5);
}
#endif

void round_(pEnv env)
{
#ifndef COMPILER
    Node node;

    PARM(1, UFLOAT);
    node = lst_pop(env->stck);
    node.u.dbl = round2(node.op == FLOAT_ ? node.u.dbl : node.u.num);
    node.op = FLOAT_;
    lst_push(env->stck, node);
#endif
}
#endif
