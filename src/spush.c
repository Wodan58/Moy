/*
    module  : spush.c
    version : 1.4
    date    : 09/11/23
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
#ifndef COMPILER
    Node jump, node;

    jump = lst_pop(env->prog);
    node = lst_at(env->prog, jump.u.num);
    lst_push(env->stck, node);
#endif
}
#endif
