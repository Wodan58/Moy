/*
    module  : cswap.c
    version : 1.9
    date    : 03/05/24
*/
#ifndef CSWAP_C
#define CSWAP_C

/**
Q0  OK  3330  #cswap  :  N  ->
Pop the location of an element from the code stack.
Swap that element with the top of the data stack.
*/
void cswap_(pEnv env)
{
    Node elem, jump, node;

    PARM(1, ANYTYPE);
    env->stck = pvec_pop(env->stck, &node);
    env->prog = pvec_pop(env->prog, &jump);
    elem = pvec_nth(env->prog, jump.u.num);
    env->prog = pvec_upd(env->prog, jump.u.num, node);	/* write node */
    env->stck = pvec_add(env->stck, elem);
}
#endif
