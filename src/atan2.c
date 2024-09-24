/*
    module  : atan2.c
    version : 1.8
    date    : 09/17/24
*/
#ifndef ATAN2_C
#define ATAN2_C

/**
Q0  OK  1520  atan2  :  DDA  F G  ->  H
H is the arc tangent of F / G.
*/
void atan2_(pEnv env)
{
    Node first, second;

    PARM(2, BFLOAT);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    first.u.dbl = atan2(first.op == FLOAT_ ? first.u.dbl : (double)first.u.num,
		    second.op == FLOAT_ ? second.u.dbl : (double)second.u.num);
    first.op = FLOAT_;
    vec_push(env->stck, first);
}
#endif
