/*
    module  : ldexp.c
    version : 1.5
    date    : 09/15/23
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
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
    first.u.dbl = ldexp(first.op == FLOAT_ ? first.u.dbl : first.u.num,
			second.u.num);
    first.op = FLOAT_;
    lst_push(env->stck, first);
}
#endif
