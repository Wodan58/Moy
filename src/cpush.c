/*
    module  : cpush.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef CPUSH_C
#define CPUSH_C

/**
OK 3290  (cpush)  :  D	->
Pop the location of an element from the code stack.
Pop an element from the data stack and store it at the given location.
*/
void cpush_(pEnv env)
{
    Node jump, node;

    PARM(1, ANYTYPE);
    jump = vec_pop(env->prog);
    node = vec_pop(env->stck);
    vec_assign(env->prog, jump.u.num, node); /* write node */
}
#endif