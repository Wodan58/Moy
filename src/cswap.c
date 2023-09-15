/*
    module  : cswap.c
    version : 1.5
    date    : 09/15/23
*/
#ifndef CSWAP_C
#define CSWAP_C

/**
OK 3330  (cswap)  :  N	->
Pop the location of an element from the code stack.
Swap that element with the top of the data stack.
*/
void cswap_(pEnv env)
{
    Node elem, jump, node;

    PARM(1, ANYTYPE);
    node = lst_pop(env->stck);
    jump = lst_pop(env->prog);
    elem = lst_at(env->prog, jump.u.num);
    lst_assign(env->prog, jump.u.num, node); /* write node */
    lst_push(env->stck, elem);
}
#endif
