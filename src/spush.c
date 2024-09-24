/*
    module  : spush.c
    version : 1.10
    date    : 09/17/24
*/
#ifndef SPUSH_C
#define SPUSH_C

/**
Q0  OK  3360  #spush  :  A  ->
Pop the location of an element on the code stack.
Read that element and push it on the data stack.
*/
void spush_(pEnv env)
{
    Node jump, node;

    jump = vec_pop(env->prog);
    node = vec_at(env->prog, jump.u.num);
    vec_push(env->stck, node);
}
#endif
