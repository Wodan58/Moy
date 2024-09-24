/*
    module  : pow.c
    version : 1.8
    date    : 09/17/24
*/
#ifndef POW_C
#define POW_C

/**
Q0  OK  1630  pow  :  DDA  F G  ->  H
H is F raised to the Gth power.
*/
void pow_(pEnv env)
{
    Node first, second;

    PARM(2, BFLOAT);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    first.u.dbl = pow(first.op == FLOAT_ ? first.u.dbl : (double)first.u.num,
		    second.op == FLOAT_ ? second.u.dbl : (double)second.u.num);
    first.op = FLOAT_;
    vec_push(env->stck, first);
}
#endif
