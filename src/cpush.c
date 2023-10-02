/*
    module  : cpush.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef CPUSH_C
#define CPUSH_C

/**
OK 3350  (cpush)  :  D	->
Pop the location of an element from the code stack.
Pop an element from the data stack and store it at the given location.
*/
void cpush_(pEnv env)
{
    Node jump, node;

    PARM(1, ANYTYPE);
    env->prog = pvec_pop(env->prog, &jump);
    env->stck = pvec_pop(env->stck, &node);
    env->prog = pvec_upd(env->prog, jump.u.num, node);	/* write node */
}
#endif
