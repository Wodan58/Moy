/*
    module  : spush.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef SPUSH_C
#define SPUSH_C

/**
OK 3300  (spush)  :  A	->
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
