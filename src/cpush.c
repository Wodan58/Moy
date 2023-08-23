/*
    module  : cpush.c
    version : 1.2
    date    : 08/23/23
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
    jump = lst_pop(env->prog);
    node = lst_pop(env->stck);
    lst_assign(env->prog, jump.u.num, node); /* write node */
}
#endif
