/*
    module  : ldexp.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef LDEXP_C
#define LDEXP_C

/**
OK 1590  ldexp  :  DDA	F I  ->  G
G is F times 2 to the Ith power.
*/
void ldexp_(pEnv env)
{
    Node first, second;

    PARM(2, LDEXP);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    first.u.dbl = ldexp(first.op == FLOAT_ ? first.u.dbl : first.u.num,
			second.u.num);
    first.op = FLOAT_;
    env->stck = pvec_add(env->stck, first);
}
#endif
