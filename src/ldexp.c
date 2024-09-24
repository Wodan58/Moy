/*
    module  : ldexp.c
    version : 1.8
    date    : 09/17/24
*/
#ifndef LDEXP_C
#define LDEXP_C

/**
Q0  OK  1590  ldexp  :  DDA  F I  ->  G
G is F times 2 to the Ith power.
*/
void ldexp_(pEnv env)
{
    Node first, second;

    PARM(2, LDEXP);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    first.u.dbl = ldexp(first.op == FLOAT_ ? first.u.dbl : first.u.num,
			second.u.num);
    first.op = FLOAT_;
    vec_push(env->stck, first);
}
#endif
