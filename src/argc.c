/*
    module  : argc.c
    version : 1.9
    date    : 10/24/24
*/
#ifndef ARGC_C
#define ARGC_C

/**
Q0  OK  3050  argc  :  A  ->  I
Pushes the number of command line arguments. This is equivalent to 'argv size'.
*/
void argc_(pEnv env)
{
    Node node;

    node.u.num = env->g_argc;
    node.op = INTEGER_;
    vec_push(env->stck, node);
}
#endif
