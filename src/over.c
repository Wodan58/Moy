/*
    module  : over.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef OVER_C
#define OVER_C

/**
OK 3220  over  :  A	X Y  ->  X Y X
Pushes an extra copy of the second item X on top of the stack.
*/
void over_(pEnv env)
{
    Node node;

    PARM(2, ANYTYPE);
    node = vec_at(env->stck, vec_size(env->stck) - 2);
    vec_push(env->stck, node);
}
#endif
