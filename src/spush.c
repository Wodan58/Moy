/*
    module  : spush.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef SPUSH_C
#define SPUSH_C

/**
OK 3360  (spush)  :  A	->
Pop the location of an element on the code stack.
Read that element and push it on the data stack.
*/
void spush_(pEnv env)
{
    Node jump, node;

    env->prog = pvec_pop(env->prog, &jump);
    node = pvec_nth(env->prog, jump.u.num);
    env->stck = pvec_add(env->stck, node);
}
#endif
