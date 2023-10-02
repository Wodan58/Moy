/*
    module  : pow.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef POW_C
#define POW_C

/**
OK 1630  pow  :  DDA	F G  ->  H
H is F raised to the Gth power.
*/
void pow_(pEnv env)
{
    Node first, second;

    PARM(2, BFLOAT);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    first.u.dbl = pow(first.op == FLOAT_ ? first.u.dbl : (double)first.u.num,
		    second.op == FLOAT_ ? second.u.dbl : (double)second.u.num);
    first.op = FLOAT_;
    env->stck = pvec_add(env->stck, first);
}
#endif
